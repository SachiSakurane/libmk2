//
// Created by Himatya on 2017/11/22.
//

#pragma once

#include <type_traits>

namespace mk2{
namespace math{

    namespace detail
    {
        template <typename T, typename = void>
        struct isnan_impl{};

        template <typename FloatType>
        struct isnan_impl<FloatType, std::enable_if_t <std::is_floating_point<FloatType>::value>>{
            inline constexpr static bool f(FloatType x)
            {
                return !(x == x);
            }
        };

        template <typename IntType>
        struct isnan_impl<IntType, std::enable_if_t <std::is_integral<IntType>::value>>{
            inline constexpr static bool f(IntType x)
            {
                return false;
            }
        };
    }

    template<typename T>
    inline constexpr bool isnan(T x)
    {
        return mk2::math::detail::isnan_impl<T>::f(x);
    }

}
}
