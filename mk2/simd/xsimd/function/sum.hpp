//
// Created by Himatya on 2018/08/07.
//

#pragma once

#include <mk2/container/container_traits.hpp>
#include <mk2/simd/xsimd/alignment_mode.hpp>

namespace mk2 { namespace simd{ namespace xsimd {
namespace function
{
    namespace detail
    {
    
    }
    
    template<class Iterator, class SourceContainer>
    [[deprecated("need implementation impl_sum, impl_sum1")]]
    decltype(auto) range_sum(const Iterator& first, const Iterator& last, const SourceContainer& source)
    {
        typedef typename mk2::container::container_traits<SourceContainer>::value_type Type;
        typedef typename alignment_mode<Container>::type AlignmentTag;
        constexpr std::size_t simd_size = xsimd::simd_type<Type>::size;
        auto size = static_cast<std::size_t>(std::distance(first, last) + 1);
        auto offset = std::distance(std::begin(source), first) % simd_size;
        //offset 最初のスカラー処理の回数
        return offset == 0
            ? detail::impl_sum<Iterator, Type, AlignmentTag>(first, last, size)
            : size < simd_size * 4
                ? detail::impl_sum1<Iterator, Type, xsimd::unaligned_mode>(first, last, size, offset)
                : detail::impl_sum1<Iterator, Type, xsimd::AlignmentTag>(first, last, size, offset);
    }
    
    template<
        class Container,
        class Type = typename mk2::container::container_traits<Container>::value_type,
        class AlignmentTag = typename alignment_mode<Container>::type>
    Type sum(const Container& rhv, size_t size)
    {
        constexpr std::size_t simd_size = xsimd::simd_type<Type>::size;
        std::size_t vec_size = size - size % simd_size;
        Type result = static_cast<Type>(0);
        
        for(std::size_t i = 0; i < vec_size; i += simd_size)
        {
            auto ba = xsimd::load_simd(&rhv[i], AlignmentTag());
            result += xsimd::hadd(ba);
        }
        
        for(std::size_t i = vec_size; i < size; ++i)
        {
            result = rhv[i];
        }
        
        return result;
    }
    
    template<
        class Container,
        class Type = typename mk2::container::container_traits<Container>::value_type,
        class AlignmentTag = typename alignment_mode<Container>::type>
    Type sum(const Container& rhv)
    {
        return sum(rhv, rhv.size());
    }
}
}
}
}