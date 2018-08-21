//
// Created by Himatya on 2018/08/21.
//

#pragma once

#include <fenv.h>

#include <mk2/container/fixed_array.hpp>
#include <mk2/simd/ipp/function/fixed_accuracy_arithmetic.hpp>
#include <mk2/simd/ipp/function/arithmetric.hpp>
#include <mk2/simd/ipp/function/conversion.hpp>
#include <mk2/simd/ipp/function/logical_shift.hpp>

namespace mk2 { namespace simd { namespace ipp {
    
    template<class Type, class DstType>
    class formant
    {
    public:
        formant(int size) :
            size_(size),
            calc_buf_(size_ - 1),
            logical_buf_(size_ - 1),
            minimul_(size_ - 2)
        {}
        
        void process(const Type* src, DstType *dst)
        {
            auto round_type = fegetround();
            
            fesetround(FE_TONEAREST);

            function::ipps_sub(src + 1, src, calc_buf_.data(), size_ - 1);
            function::ipps_addc_inplace(static_cast<Type>(0.5), calc_buf_.data(), size_ - 1);
            function::ipps_near_by_int(calc_buf_.data(), calc_buf_.data(), static_cast<int>(calc_buf_.size()));
            function::ipps_convert_f2i(calc_buf_.data(), logical_buf_.data(), static_cast<int>(logical_buf_.size()));
    
            function::ipps_xor(logical_buf_.data(), logical_buf_.data() + 1, dst + 1, static_cast<int>(minimul_.size()));
            dst[0] = dst[size_ - 1] = 0;

            fesetround(round_type);
        }
        
    private:
        const int size_;
        mk2::container::fixed_array<Type> calc_buf_;
        mk2::container::fixed_array<DstType> logical_buf_;
        mk2::container::fixed_array<DstType> minimul_;
    };
    
}}}