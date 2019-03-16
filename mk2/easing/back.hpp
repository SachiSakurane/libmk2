//
//  back.hpp
//
//
//  Created by Himatya on 2017/05/26.
//  Copyright (c) 2017 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

namespace mk2{
namespace easing{
    template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T back(T normalized_time){
        return normalized_time * normalized_time * (2.70158 * normalized_time - 1.70158);
    }
}
}
