//
//  elastic.hpp
//
//
//  Created by Himatya on 2017/05/26.
//  Copyright (c) 2017 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

#include <mk2/math/constants.hpp>
#include <mk2/math/pow.hpp>
#include <mk2/math/sin.hpp>

namespace mk2{
namespace easing{

    struct elastic
    {
        template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        constexpr T operator()(T normalized_time)
        {
            if ( normalized_time == 0 ) return 0;
            if ( normalized_time == 1 ) return 1;
            T mrvs_time = normalized_time - 1;
            T post_fix = mk2::math::pow( 2.0, 10.0 * mrvs_time);
            return - (post_fix * mk2::math::sin((mrvs_time - 0.075) * mk2::math::two_pi<T> * 3.33333333));
        }
    };

}
}

