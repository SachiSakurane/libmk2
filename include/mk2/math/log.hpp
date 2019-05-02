//
//  log.hpp
//
//
//  Created by Himatya on 2017/02/11.
//  Copyright (c) 2017 Himatya. All rights reserved.
//

#pragma once

#include <limits>
#include <type_traits>

#include <mk2/math/constants.hpp>
#include <mk2/math/factorial.hpp>
#include <mk2/math/sqrt.hpp>
#include <mk2/math/isnan.hpp>

namespace mk2{
namespace math{
    namespace detail{
        template<typename T>
        inline constexpr T log_impl_3(T x, T powval, std::size_t n, std::size_t last){
            return (
                n % 2 ? powval / static_cast<T>(n)
                    : -powval / static_cast<T>(n)
                ) + (n == last ? static_cast<T>(0.0) : mk2::math::detail::log_impl_3(x, powval * x, n + 1, last));
        }

        template<typename T>
        inline constexpr T log_impl_2(T x, std::size_t n, std::size_t last)
        {
            return mk2::math::detail::log_impl_3(x, x, n, last);
        }
        
        template<typename T>
        inline constexpr T log_impl_1(T x){
            return x > mk2::math::root_two<T> ? static_cast<T>(2) * mk2::math::detail::log_impl_1(mk2::math::sqrt(x))
                : mk2::math::detail::log_impl_2(x - static_cast<T>(1), 1, mk2::math::detail::factorial_table<T>.size() - 1);
        }
        
        template<typename T>
        inline constexpr T log_impl(T x){
            return x < static_cast<T>(1) ? - mk2::math::detail::log_impl_1(static_cast<T>(1) / x)
                : mk2::math::detail::log_impl_1(x);
        }

        template<typename T>
        inline constexpr T log_impl_(T x)
        {
            return mk2::math::isnan(x) ? x
                : x == 0 ? -std::numeric_limits<T>::infinity()
                : x == std::numeric_limits<T>::infinity() ? x
                : x < 0 ? std::numeric_limits<T>::quiet_NaN()
                : x == 1 ? 0
                : log_impl(x);

        }
    }
    
    template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T log(T x){
        return mk2::math::detail::log_impl_(x);
    }
}
}
