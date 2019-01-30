//
// Created by Himatya on 2019-01-30.
//

#pragma once

#include <memory>

#include <mk2/container/fixed_array.hpp>
#include <mk2/math/constants.hpp>
#include <mk2/simd/ipp/function/sampling.hpp>
#include <mk2/simd/ipp/bi_quad_filter.hpp>

namespace mk2 { namespace simd { namespace ipp{

    template<class Type>
    class oversampling
    {
    public:
        oversampling(int max_sample, int factor_order, float sample_rate)
        : max_sample_(max_sample),
          factor_order_(factor_order),
          factor_(1 << factor_order),
          sample_rate_(sample_rate),
          buffer0_(static_cast<size_t>(max_sample_ * factor_)),
          filter_(static_cast<size_t>(factor_order))
        {
            for (int i = 0; i < factor_order; ++i)
            {
                int local_factor = 1 << (i + 1);
                filter_[i] = std::make_unique<mk2::simd::ipp::bi_quad_filter<Type>>(
                        sample_rate * local_factor,
                        mk2::simd::ipp::bi_quad_coefficients::low_pass(sample_rate / 2.f, mk2::math::inv_root_two<float>));
            }
        }

        void operator()(const Type* src, Type* dst, int len)
        {
            namespace ipf = mk2::simd::ipp::function;

            ipf::copy(src, buffer0_.data(), len);

            for (int i = 0; i < factor_order_; ++i)
            {
                int size = len * (1 << i);
                int dst_len, pphase = 0;
                ipf::sample_up(buffer0_.data(), size, dst, &dst_len, 2, &pphase);
                ipf::copy(dst, buffer0_.data(), dst_len);

                filter_[i]->operator()(buffer0_.data(), buffer0_.data(), dst_len);
            }

            ipf::copy(buffer0_.data(), dst, len * factor_);
        }

    private:
        const int max_sample_, factor_order_, factor_;
        float sample_rate_;
        mk2::container::fixed_array<Type> buffer0_;
        mk2::container::fixed_array<std::unique_ptr<mk2::simd::ipp::bi_quad_filter<Type>>> filter_;

    };

}}}