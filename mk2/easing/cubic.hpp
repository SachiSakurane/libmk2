//
//  cubic.hpp
//
//
//  Created by Himatya on 2017/02/09.
//  Copyright (c) 2017 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

namespace mk2{
namespace easing{
    template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T cubic(T normalized_time){
        return normalized_time * normalized_time * normalized_time;
    }
}
}

