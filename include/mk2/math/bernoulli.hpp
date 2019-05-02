//
//  bernoulli.hpp
//
//
//  Created by Himatya on 2017/02/06.
//  Copyright (c) 2017 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

#include <mk2/math/binomial_coefficient.hpp>

namespace mk2{
namespace math{
    namespace detail{
        /*
        template<typename T>
        inline constexpr T bernoulli_impl2(const std::size_t);
        
        template<typename T>
        inline constexpr T bernoulli_impl2(const std::size_t n){
            return n ? -(1 / static_cast<T>(n + 1)) * bernoulli_impl3<T>(n, 0) : static_cast<T>(1);
        }
        
        template<typename T>
        inline constexpr T bernoulli_impl3(const std::size_t n, const std::size_t k){
            return k < n
            ? mk2::math::detail::bernoulli_impl2<T>(k) * mk2::math::binoial_coefficient<T>(n + 1, k)
            + mk2::math::detail::bernoulli_impl3<T>(n, k + 1)
            : static_cast<T>(0);
        }
        */
        
        template<typename T>
        inline constexpr T bernoulli_impl(const std::size_t n){
            if(!n)return 1;
            T result = 0;
            for(std::size_t k = 0; k < n; ++k){
                result += mk2::math::binomial_coefficient<T>(n + 1, k) * bernoulli_impl<T>(k);
            }
            result /= -static_cast<T>(n + 1);
            return result;
        }
    }
    
    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    inline constexpr T bernoulli(std::size_t val){
        return mk2::math::detail::bernoulli_impl<T>(val);
    }
    
}
}
