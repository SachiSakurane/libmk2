//
// Created by Himatya on 2018-12-22.
//

#pragma once

#include <memory>

#include <mk2/container/fixed_array.hpp>
#include <mk2/simd/ipp/ipp_buffer_delete.hpp>
#include <mk2/simd/ipp/type.hpp>
#include <mk2/simd/ipp/ring_buffer.hpp>
#include <mk2/simd/ipp/function/filtering.hpp>

namespace mk2 { namespace simd { namespace ipp
{

    template <class Type, bool AutoDelay = false>
    class fir_sr
    {
        template <class ContainType>
        using ptr_type = std::unique_ptr<ContainType, mk2::simd::ipp::ipp_buffer_delete<ContainType>>;
        using spec_type = mk2::simd::ipp::ipps_fir_spec<Type>;

    public:
        explicit fir_sr (const Type* taps, int taps_len)
            : taps_len_(taps_len),
              taps_(static_cast<size_t>(taps_len_ * 2 - 1)),
              delay_(static_cast<size_t>(taps_len - 1 >= 0 ? taps_len - 1 : 0), 0),
              delay_buffer_(delay_.size())
        {
            function::copy(taps, taps_.data(), taps_len_);

            int spec_size, buf_size;
            ippsFIRSRGetSize(taps_len_, ipp_data_type<Type>, &spec_size, &buf_size);

            buffer_ = ptr_type<Ipp8u>(ippsMalloc_8u(buf_size));
            spec_ = ptr_type<spec_type>(reinterpret_cast<spec_type*>(ippsMalloc_8u(spec_size)));

            function::fir_sr_init(taps_.data(), taps_len, ippAlgDirect, spec_.get());
        }

        void operator()(const Type* src, Type* dst, int len)
        {
            delay_.copy_aligned_data(delay_buffer_.data(), delay_buffer_.size());
            function::fir_sr(src, dst, len, spec_.get(), delay_buffer_.data(), (Type*) nullptr, buffer_.get());
            delay_.set_sample(src, len);
        }

        const int get_taps_len() const { return taps_len_; }
        const double get_delay() const { return static_cast<double>(taps_len_); }

    private:
        const int taps_len_;
        ptr_type<Ipp8u> buffer_;
        ptr_type<spec_type> spec_;
        ring_buffer<Type> delay_;
        mk2::container::fixed_array<Type> delay_buffer_;
        mk2::container::fixed_array<Type> taps_;

    };

    template <class Type>
    class fir_sr<Type, true>
    {
        template <class ContainType>
        using ptr_type = std::unique_ptr<ContainType, mk2::simd::ipp::ipp_buffer_delete<ContainType>>;
        using spec_type = mk2::simd::ipp::ipps_fir_spec<Type>;

    public:
        explicit fir_sr (const Type* taps, int taps_len)
                : taps_len_(taps_len),
                  taps_(static_cast<size_t>(taps_len_ * 2 - 1))
        {
            function::copy(taps, taps_.data(), taps_len_);

            int spec_size, buf_size;
            ippsFIRSRGetSize(taps_len_, ipp_data_type<Type>, &spec_size, &buf_size);

            buffer_ = ptr_type<Ipp8u>(ippsMalloc_8u(buf_size));
            spec_ = ptr_type<spec_type>(reinterpret_cast<spec_type*>(ippsMalloc_8u(spec_size)));

            function::fir_sr_init(taps_.data(), taps_len, ippAlgDirect, spec_.data());
        }

        void operator()(const Type* src, Type* dst, const Type* delay_src, Type* delay_dst, int len)
        {
            function::fir_sr(src, dst, len, spec_.get(), delay_src, delay_dst, buffer_.get());
        }

        const int get_taps_len() const { return taps_len_; }
        const double get_delay() const { return static_cast<double>(taps_len_); }

    private:
        const int taps_len_;
        ptr_type<Ipp8u> buffer_;
        ptr_type<spec_type> spec_;
        mk2::container::fixed_array<Type> taps_;

    };

    template <class Type>
    class iir
    {
        using ptr_type = std::unique_ptr<Ipp8u, mk2::simd::ipp::ipp_buffer_delete<Ipp8u>>;
        using state_type = mk2::simd::ipp::ipps_iir_state<Type>;

    public:
        explicit iir (int order)
            : order_(order),
              coefficients_(static_cast<size_t>(order_ + 1) * 2)
        {
            int buf_size;
            function::iir_get_state_size<Type>(order_, &buf_size);
            ptr_type buffer = ptr_type(ippsMalloc_8u(buf_size));

            function::iir_init(&state_, coefficients_.data(), order_, nullptr, buffer.get());
        }

        void set_coefficients(const float* cofs)
        {
            function::copy(cofs, coefficients_.data(), static_cast<int>(coefficients_.size()));
        }

        void operator()(const Type* src, Type* dst, int len)
        {
            function::iir(src, dst, len, state_);
        }

        void inplace(Type* src_dst, int len)
        {
            function::iir_inplace(src_dst, len, state_);
        }

    private:
        const int order_;
        state_type *state_;
        mk2::container::fixed_array<Type> coefficients_;

    };

}}}