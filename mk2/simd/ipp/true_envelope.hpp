//
// Created by Himatya on 2018/11/21.
//

#pragma once

#include <cstddef>
#include <memory>
#include <limits>

#include <mk2/container/fixed_array.hpp>
#include <mk2/simd/ipp/ipp_buffer_delete.hpp>
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
        using ptr_type = std::unique_ptr<Type, ipp_buffer_delete>;
        using spec_type = mk2::simd::ipp::ipps_fft_spec_c<Type>;
    
    public:
        true_envelope(int order) : 
            fft_(order), im_buffer_(1 << order), cepstrum_(1 << order)
        {}
        
        ~true_envelope() = default;
        
        IppStatus operator()(const Type* src_re, const Type* src_im, Type* dst, std::size_t iteration, std::size_t threshold, bool inverse = true)
        {
            using ipf = mk2::simd::ipp::function;
            const int size = static_cast<int>(im_buffer_.size());
            auto err = ippStsNoErr;
            
            // spectrum
            fft_(src_re, src_im, dst, im_buffer_.data());
            ipf::power_spectr(dst, im_buffer_.data(), dst, size);
            ipf::ln(dst, dst, size, mk2::simd::ipp::precision_high);
            
            if (iteration <= 1)
                return err;
            
            ipf::copy(dst, cepstrum_.data(), size);
            
            // true spectrum iteration
            for (int i = 1; i < iteration; ++i)
            {
                ipf::zero(im_buffer_.data(), size);
                
                if (inverse) fft_.inverse_inplace(cepstrum_.data(), im_buffer_.data());
                else         fft_.inplace(cepstrum_.data(), im_buffer_.data());
                
                ipf::zero(cepstrum_.data() + threshold, size - threshold);
                
                if (inverse) fft_.inplace(cepstrum_.data(), im_buffer_.data());
                else         fft_.inverse_inplace(cepstrum_.data(), im_buffer_.data());
                
                ipf::max_every_inplace(cepstrum_.data(), dst, size);
            }
            
            return err;
        }
        
    private:
        mk2::container::fixed_array<Type> im_buffer_;
        mk2::container::fixed_array<Type> cepstrum_;
        mk2::simd::ipp::fft fft_;
        
    };

}}}