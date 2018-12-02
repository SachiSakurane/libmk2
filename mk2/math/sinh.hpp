//
//  sinh.hpp
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
        inline constexpr T sinh_maclaurin_impl(T x, std::size_t last, std::size_t n, T powval){
            return powval * math::inverse_factorial<T>((n << 1) + 1) + (
            n == last
                ? static_cast<T>(0.0)
                : sinh_maclaurin_impl(x, last, n + 1, powval * x * x));
        }
    }
    template<class T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T sinh(T x){
        return math::detail::sinh_maclaurin_impl(x, (mk2::math::detail::factorial_table<T>.size() - 2) >> 1, 0, x);
    }
}
}
