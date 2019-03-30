//
//  exp.hpp
//
//
//  Created by Himatya on 2017/02/24.
//  Copyright (c) 2017 Himatya. All rights reserved.
//

#pragma once

#include <limits>
#include <type_traits>

#include <mk2/math/constants.hpp>
#include <mk2/math/isnan.hpp>
#include <mk2/math/factorial.hpp>

namespace mk2{
namespace math{
    namespace detail{
        template<class T>
        inline constexpr T exp_impl1(T x, T powval,  std::size_t n, std::size_t last){
            return powval * mk2::math::inverse_factorial<T>(n) + (n == last ? static_cast<T>(0.0) : exp_impl1(x, powval * x, n + 1, last));
        }

        template<class T>
        inline constexpr T exp_impl(T x){
            return mk2::math::isnan(x) ? x
                : x == -std::numeric_limits<T>::infinity() ? 0
                : x == 0 ? 1
                : x == 1 ? mk2::math::e<T>
                : x == std::numeric_limits<T>::infinity() ? std::numeric_limits<T>::infinity()
                : exp_impl1(x, static_cast<T>(1), 0, mk2::math::detail::factorial_table<T>.size() - 1);

        }
    }
    
    template<class T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T exp(T x){
        return math::detail::exp_impl(x);
    }
}
}

