//
// Created by Himatya on 2019-03-25.
//

#pragma once

#include <type_traits>

#include <mk2/math/constants.hpp>
#include <mk2/math/sin.hpp>

namespace mk2{
namespace math{
    template<class T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T sync(T x)
    {
        return x == 0 ? 1 : mk2::math::sin(x) / x;
    }

    template<class T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T normalized_sync(T x)
    {
        const auto pi_x = x * mk2::math::pi<T>;
        return x == 0 ? 1 : sin(pi_x) / pi_x;
    }
}}