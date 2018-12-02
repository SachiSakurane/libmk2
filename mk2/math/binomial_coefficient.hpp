//
//  binomial_coefficient.hpp
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
    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    inline constexpr T binomial_coefficient(const std::size_t n, const std::size_t r){
        return mk2::math::factorial<T>(n) * mk2::math::inverse_factorial<T>(r) * mk2::math::inverse_factorial<T>(n - r);
    }
}
}
