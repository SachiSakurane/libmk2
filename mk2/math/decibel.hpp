//
// Created by Himatya on 2017/11/22.
//

#pragma once

#include <type_traits>

#include <mk2/math/abs.hpp>
#include <mk2/math/log10.hpp>
#include <mk2/math/pow.hpp>

namespace mk2 {
namespace math {
    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    inline constexpr T gain_to_decibel(T amplitude)
    {
        return T(20) * mk2::math::log10(mk2::math::abs(amplitude));
    }

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    inline constexpr T decibel_to_gain(T decibel)
    {
        return mk2::math::pow (T(10.0), decibel * T(0.05));
    }
}
}
