//
//  circular.hpp
//
//
//  Created by Himatya on 2017/05/26.
//  Copyright (c) 2017 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>
#include <mk2/math/sqrt.hpp>

namespace mk2{
namespace easing{

    struct circular_t
    {
        template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        constexpr T operator()(T normalized_time)
        {
            return static_cast<T>(1) - mk2::math::sqrt(static_cast<T>(1) - normalized_time * normalized_time);
        }
    };

    static constexpr circular_t circular = circular_t{};

}
}
