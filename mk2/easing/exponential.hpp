//
//  exponential.hpp
//
//
//  Created by Himatya on 2017/02/09.
//  Copyright (c) 2017 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

#include <mk2/math/pow.hpp>

namespace mk2{
namespace easing{

    struct exponential
    {
        template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        constexpr T operator()(T normalized_time)
        {
            return mk2::math::pow(static_cast<T>(2), static_cast<T>(10.0 * (normalized_time - 1.0)));
        }
    };

}
}

