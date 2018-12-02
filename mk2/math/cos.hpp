//
//  cos.hpp
//
//
//  Created by Himatya on 2015/12/20.
//  Copyright (c) 2015 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

#include <mk2/math/factorial.hpp>

namespace mk2{
namespace math{
    namespace detail{
        template<class T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        inline constexpr T cos_impl(T x, std::size_t last, std::size_t n, T powval = static_cast<T>(1)){
            return (
                n % 2
                    ? -powval * math::inverse_factorial<T>(n << 1)
                    : powval * math::inverse_factorial<T>(n << 1)
                ) + (n == last ? static_cast<T>(0.0) : cos_impl(x, last, n + 1, powval * x * x));
        }
    }
    
    template<class T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T cos(T x){
        return math::detail::cos_impl(x, (mk2::math::detail::factorial_table<T>.size() - 1) >> 1, 0);
    }
}
}
