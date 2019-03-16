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
    template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T circular(T normalized_time){
        return 1.0 - mk2::math::sqrt(1.0 - normalized_time * normalized_time);
    }
}
}
