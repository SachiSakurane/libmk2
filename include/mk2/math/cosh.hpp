//
//  cosh.hpp
//
//
//  Created by Himatya on 2017/02/07.
//  Copyright (c) 2017 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

#include <mk2/math/factorial.hpp>

namespace mk2{
namespace math{
    namespace detail{
        template<class T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        inline constexpr T cosh_impl(T x, std::size_t last, std::size_t n, T powval){
            return powval * math::inverse_factorial<T>(n << 1) + (
            n == last
                ? static_cast<T>(0.0)
                : cosh_impl(x, last, n + 1, powval * x * x));
        }
    }
    template<class T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T cosh(T x){
        return math::detail::cosh_impl(x, (mk2::math::detail::factorial_table<T>.size() - 1) >> 1, 0, static_cast<T>(1));
    }
}
}
