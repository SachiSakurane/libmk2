//
// Created by Himatya on 2018/08/21.
//

#pragma once

#include <cfenv>
#include <type_traits>

#include <mk2/container/fixed_array.hpp>
#include <mk2/simd/ipp/function/fixed_accuracy_arithmetic.hpp>
#include <mk2/simd/ipp/function/arithmetric.hpp>
#include <mk2/simd/ipp/function/conversion.hpp>
#include <mk2/simd/ipp/function/logical_shift.hpp>

namespace mk2 { namespace simd { namespace ipp {
    
    template<class SrcType, class IndexType = Ipp8u>
    class extremum_index
    {
    public:
        formant(int size) :
            size_(size),
            dif_buf_(size_ - 1),
            logical_buf_(size_ - 1)
        {}
        
        void operator()(const SrcType* src, IndexType *dst)
        {
            auto round_type = std::fegetround();
            
            fesetround(FE_TONEAREST);

            // differential
            function::ipps_sub(src + 1, src, dif_buf_.data(), size_ - 1);
            // ceiling
            //function::ipps_addc_inplace(static_cast<SrcType>(0.5), dif_buf_.data(), static_cast<int>(dif_buf_.size()));
            function::ipps_ceil(dif_buf_.data(), dif_buf_.data(), static_cast<int>(dif_buf_.size()));
            // to logical(with -v -> 0)
            function::ipps_convert_f2i(calc_buf_.data(), logical_buf_.data(), static_cast<int>(logical_buf_.size()));
            
            // maximul
            function::ipps_xor(logical_buf_.data(), logical_buf_.data() + 1, dst + 1, size_ - 2);
            dst[0] = dst[size_ - 1] = 0;

            std::fesetround(round_type);
        }
        
    private:
        const int size_;
        mk2::container::fixed_array<SrcType> dif_buf_;
        mk2::container::fixed_array<IndexType> logical_buf_;
    };
    
}}}