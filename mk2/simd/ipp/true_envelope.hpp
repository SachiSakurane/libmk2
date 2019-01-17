//
// Created by Himatya on 2018/11/21.
//

#pragma once

#include <cstddef>
#include <memory>
#include <limits>

#include <mk2/container/fixed_array.hpp>
#include <mk2/simd/ipp/type.hpp>
#include <mk2/simd/ipp/fft.hpp>
#include <mk2/simd/ipp/function/conversion.hpp>
#include <mk2/simd/ipp/function/fixed_accuracy_arithmetic.hpp>
#include <mk2/simd/ipp/function/initialization.hpp>
#include <mk2/simd/ipp/function/statistical.hpp>

namespace mk2 { namespace simd { namespace ipp {
    
    template <class Type>
    class true_envelope
    {
    public:
        explicit true_envelope(int order) :
            fft_(order), buffer_(static_cast<std::size_t>(1 << order)), buffer_im_(static_cast<std::size_t>(1 << order))
        {}
        
        ~true_envelope() = default;
        
        IppStatus operator()(const Type* src_spec, Type* dst_env, Type threshold_db, int lifter, bool is_half = false, std::size_t max_iteration = 32)
        {
            namespace ipf = mk2::simd::ipp::function;

            const int size = static_cast<int>(buffer_.size());
            const int half = size / 2;
            auto err = ippStsNoErr;

            Type max_dif = std::numeric_limits<Type>::infinity();

            err |= ipf::copy(src_spec, buffer_.data(), half);

            // true spectrum iteration
            for (std::size_t i = 0; i < max_iteration && max_dif > threshold_db; ++i)
            {
                if (i > 0)
                    err |= ipf::max_every_inplace(src_spec, buffer_.data(), half);

                err |= ipf::zero(buffer_im_.data(), size);
                err |= ipf::flip(buffer_.data(), buffer_.data() + half, half);

                // ifft
                err |= fft_.inverse_inplace(buffer_.data(), buffer_im_.data());

                // liftering
                if (size - lifter * 2 > 0)
                    err |= ipf::zero(buffer_.data() + lifter, size - lifter * 2);

                // fft
                err |= ipf::zero(buffer_im_.data(), size);
                err |= fft_.forward_inplace(buffer_.data(), buffer_im_.data());
                err |= ipf::mulc_inplace(Type(1) / size, buffer_.data(), half);
                if (i % 2 == 0)
                    err |= ipf::copy(buffer_.data() + 1, buffer_.data(), half);

                err |= ipf::sub(src_spec, buffer_.data(), dst_env, half);
                err |= ipf::max(dst_env, half, &max_dif);
            }

            err |= ipf::copy(buffer_.data(), dst_env, half);

            if (!is_half)
                ipf::flip(dst_env, dst_env + half, half);

            return err;
        }
        
    private:
        mk2::simd::ipp::fft<Type> fft_;
        mk2::container::fixed_array<Type> buffer_;
        mk2::container::fixed_array<Type> buffer_im_;
        
    };

}}}