//
//  atan.hpp
//
//
//  Created by Himatya on 2017/02/07.
//  Copyright (c) 2017 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

#include <mk2/math/factorial.hpp>

//1 < |x| return NaN

//https://opensource.apple.com/source/Libm/Libm-2026/Source/Intel/
//https://opensource.apple.com/source/Libm/Libm-2026/Source/Intel/atan.c

namespace mk2{
namespace math{
    namespace detail{
        template<class T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        inline constexpr T atan_impl_1(T xx){
            return ;
        }
        
        template<class T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        inline constexpr T atan_impl_0(T x){
            return 0;
        }
        
        template<class T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        inline constexpr T atan_impl(T x){
            return x > 0 ? atan_impl_0(x) : -atan_impl_0(-x);
        }
        
    }
    template<class T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T atan(T x){
        return mk2::math::detail::atan_impl(x);
    }
}
}

