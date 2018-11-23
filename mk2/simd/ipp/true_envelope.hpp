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
#include <mk2/simd/ipp/conversion.hpp>
#include <mk2/simd/ipp/fixed_accuracy_arithmetic.hpp>
#include <mk2/simd/ipp/initialization.hpp>
#include <mk2/simd/ipp/statistical.hpp>

namespace mk2 { namespace simd { namespace ipp {
    
    template <class Type>
    class true_envelope
    {
    public:
        true_envelope(int order) : 
            fft_(order), calc_buffer_(1 << order), spectrum_(1 << order), cepstrum_(1 << order)
        {}
        
        ~true_envelope() = default;
        
        IppStatus operator()(const Type* src_re, const Type* src_im, Type* dst, Type threshold_db, std::size_t lifter, std::size_t max_iteration = 16, bool inverse = true)
        {
            using ipf = mk2::simd::ipp::function;
            const int size = static_cast<int>(calc_buffer_.size());
            auto err = ippStsNoErr;
            
            // power spectrum
            err |= fft_.forward(src_re, src_im, spectrum_.data(), calc_buffer_.data());
            err |= ipf::power_spectr(spectrum_.data(), calc_buffer_.data(), spectrum_.data(), size);
            err |= ipf::log(spectrum_.data(), spectrum_.data(), size, mk2::simd::ipp::precision_high);
            
            err |= ipf::copy(spectrum_.data(), dst, size);
            
            Type max_dif = std::numeric_limits<Type>::infnity();
            
            // true spectrum iteration
            for (std::size_t i = 1; i < max_iteration && max_dif > threshold_db; ++i)
            {
                err |= ipf::zero(calc_buffer_.data(), size);
                
                if (inverse) err |= fft_.inverse(dst, calc_buffer_.data(), cepstrum_.data(), calc_buffer_.data());
                else         err |= fft_.forward(dst, calc_buffer_.data(), cepstrum_.data(), calc_buffer_.data());
                
                // liftering
                err |= ipf::zero(cepstrum_.data() + lifter, size - lifter);
                
                if (inverse) err |= fft_.forward_inplace(cepstrum_.data(), calc_buffer_.data());
                else         err |= fft_.inverse_inplace(cepstrum_.data(), calc_buffer_.data());
                
                err |= ipf::max_every_inplace(cepstrum_.data(), dst, size);
                
                err |= ipf::sub(spectrum_.data(), dst, calc_buffer_.data());
                err |= ipf::max(calc_buffer_.data(), size, &max_dif);
            }
            
            return err;
        }
        
    private:
        mk2::container::fixed_array<Type> calc_buffer_;
        mk2::container::fixed_array<Type> spectrum_;
        mk2::container::fixed_array<Type> cepstrum_;
        mk2::simd::ipp::fft fft_;
        
    };

}}}