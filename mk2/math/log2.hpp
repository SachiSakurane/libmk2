//
// Created by Himatya on 2018/09/09.
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
        inline constexpr T log2_impl(T x){
            return mk2::math::log(x) / mk2::math::ln_two<T>;
        }

        template<typename T>
        inline constexpr T log2_impl_(T x)
        {
            return mk2::math::isnan(x) ? x
                : x == 0 ? -std::numeric_limits<T>::infinity()
                : x == std::numeric_limits<T>::infinity() ? x
                : x < 0 ? std::numeric_limits<T>::quiet_NaN()
                : x == 1 ? 0
                : log2_impl(x);
        }
    }

    template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T log2(T x)
    {
        return mk2::math::detail::log2_impl_(x);
    }
}
}