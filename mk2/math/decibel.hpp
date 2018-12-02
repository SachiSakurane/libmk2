//
// Created by Himatya on 2017/11/22.
//

#pragma once

#include <type_traits>

#include <mk2/math/abs.hpp>
#include <mk2/math/log10.hpp>

namespace mk2 {
namespace math {
    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    inline constexpr T gain_to_decibel(T amplitude)
    {
        return T(20) * mk2::math::log10(mk2::math::abs(amplitude));
    }
}
}
