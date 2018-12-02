//
// Created by Himatya on 2017/11/22.
//

#pragma once

#include <limits>
#include <type_traits>

#include <mk2/math/constants.hpp>
#include <mk2/math/log.hpp>

namespace mk2{
namespace math{

    namespace detail
    {
        template<typename T>
        inline constexpr T log10_impl1(T x)
        {
            return mk2::math::log(x) / mk2::math::ln_ten<T>;
        }

        template<typename T>
        inline constexpr T log10_impl(T x)
        {
            return mk2::math::isnan(x) ? x
                 : x == 0 ? -std::numeric_limits<T>::infinity()
                 : x == std::numeric_limits<T>::infinity() ? x
                 : x < 0 ? std::numeric_limits<T>::quiet_NaN()
                 : x == 1 ? 0
                 : log10_impl1(x);
        }
    }

    template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T log10(T x){
        return mk2::math::detail::log10_impl(x);
    }
}
}
