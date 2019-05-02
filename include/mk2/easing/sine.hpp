//
//  sine.hpp
//
//
//  Created by Himatya on 2017/02/09.
//  Copyright (c) 2017 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

#include <mk2/math/constants.hpp>
#include <mk2/math/cos.hpp>

namespace mk2{
namespace easing{

    struct sine
    {
        template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        constexpr T operator()(T normalized_time)
        {
            return 1.0 - mk2::math::cos(mk2::math::half_pi<T> * normalized_time);
        }
    };

}
}
