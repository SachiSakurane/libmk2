//
// Created by Himatya on 2018/08/21.
//

#pragma once

#include <type_traits>

#include <mk2/container/fixed_array.hpp>
#include <mk2/simd/ipp/function/fixed_accuracy_arithmetic.hpp>
#include <mk2/simd/ipp/function/arithmetic.hpp>
#include <mk2/simd/ipp/function/conversion.hpp>
#include <mk2/simd/ipp/function/logical_shift.hpp>

namespace mk2 { namespace simd { namespace ipp {
    
    enum class extremum_type
    {
        kExtremum,
        kMaximal,
        kMinimal,
    };
    
    template<class SrcType, class IndexType = Ipp8u>
    class extremum_index
    {
    public:
        extremum_index(size_t size) :
            size_((int)size),
            dif_buf_(size_ - 1),
            logical_buf_(size_ - 1)
        {}
        
        void operator()(const SrcType* src, IndexType *dst, extremum_type type = extremum_type::kExtremum)
        {
            // differential
            function::sub(src + 1, src, dif_buf_.data(), size_ - 1);
            // ceiling
            function::ceil(dif_buf_.data(), dif_buf_.data(), static_cast<int>(dif_buf_.size()));
            // threshold(+v -> 1)(-v -> 0)
            function::threshold_gt_inplace(dif_buf_.data(), static_cast<int>(dif_buf_.size()), static_cast<SrcType>(1));
            function::threshold_lt_inplace(dif_buf_.data(), static_cast<int>(dif_buf_.size()), static_cast<SrcType>(0));
            // to logical
            function::convert_f2i(dif_buf_.data(), logical_buf_.data(), static_cast<int>(logical_buf_.size()));

            // extremum detection
            function::bit_xor(logical_buf_.data(), logical_buf_.data() + 1, dst + 1, size_ - 2);
            dst[0] = dst[size_ - 1] = 0;

            switch(type)
            {
                case extremum_type::kExtremum:
                    break;
                
                case extremum_type::kMaximal:
                    function::bit_and_inplace(logical_buf_.data(), dst, static_cast<int>(logical_buf_.size()));
                    break;
                
                case extremum_type::kMinimal:
                    function::bit_and_inplace(logical_buf_.data(), dst + 1, static_cast<int>(logical_buf_.size()));
                    break;
            }
        }
        
    private:
        const int size_;
        mk2::container::fixed_array<SrcType> dif_buf_;
        mk2::container::fixed_array<IndexType> logical_buf_;
    };
    
}}}