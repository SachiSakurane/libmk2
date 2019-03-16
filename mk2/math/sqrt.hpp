//
//  sqrt.hpp
//
//
//  Created by Himatya on 2015/12/18.
//  Copyright (c) 2015 Himatya. All rights reserved.
//

#pragma once

#include <limits>
#include <type_traits>
#include <utility>

#include <mk2/math/isnan.hpp>

namespace mk2{
namespace math{

    namespace detail{

        //http://www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi

        template<typename _T>
        struct sqrt_union_int {};

        template<>
        struct sqrt_union_int<float>
        {
            typedef int32_t type;
        };

        template<>
        struct sqrt_union_int<double>
        {
            typedef int64_t type;
        };

        template<>
        struct sqrt_union_int<long double>
        {
            typedef __int128_t type;
        };

        template<typename FloatType>
        using sqrt_union_int_t = typename sqrt_union_int<FloatType>::type;

        template<typename FloatType>
        inline constexpr FloatType babylonian_sqrt_impl(sqrt_union_int_t<FloatType> v)
        {
            return 0;
        }

        //1 << 29 <- The bit at the top of the exponent part
        //1 << 22 <- The bit at the bottom of the exponent part
        template<>
        inline constexpr float babylonian_sqrt_impl<float>(sqrt_union_int_t<float> v)
        {
            return ((int32_t)1 << 29) + (v >> 1) - ((int32_t)1 << 22);
        }

        template<>
        inline constexpr double babylonian_sqrt_impl<double>(sqrt_union_int_t<double> v)
        {
            return ((int64_t)1 << 61) + (v >> 1) - ((int64_t)1 << 51);
        }

        template<>
        inline constexpr long double babylonian_sqrt_impl<long double>(sqrt_union_int_t<long double> v)
        {
            return ((__int128_t)1 << 125) + (v >> 1) - ((__int128_t)1 << 111);
        }

        //http://forums.techarena.in/software-development/1290144.htm
        template<typename _T>
        inline constexpr _T sqrt_impl2(_T x)
        {
            union{
                _T x;
                mk2::math::detail::sqrt_union_int_t<_T> i;
            }u;

            u.x = x;
            u.i = mk2::math::detail::babylonian_sqrt_impl<_T>(u.i);

            u.x = u.x + x/u.x;
            u.x = 0.25 * u.x + x/u.x;

            return u.x;
        }

        template<typename _T>
        inline constexpr _T sqrt_impl1(_T x, _T s, _T s2)
        {
            return !(s < s2) ? s2
                             : sqrt_impl1(x, (x / s + s) * _T(0.5), s);
        }

        template<typename _T>
        inline constexpr _T sqrt_impl(_T x)
        {
            return mk2::math::isnan(x) ? x
                : x < 0 ? std::numeric_limits<_T>::quiet_NaN()
                : x == 0 ? 0
                : x == 1 ? 1
                : x == std::numeric_limits<_T>::infinity() ? std::numeric_limits<_T>::infinity()
                : mk2::math::detail::sqrt_impl1(
                    x,
                    mk2::math::detail::sqrt_impl2(x),
                    x > 1 ? x : 1);
        }
    }

    template<typename _T, typename = typename std::enable_if<std::is_floating_point<_T>::value>::type>
    inline constexpr _T sqrt(_T x)
    {
        return mk2::math::detail::sqrt_impl(x);
    }
}
}
