//
//  quart.hpp
//
//
//  Created by Himatya on 2017/02/09.
//  Copyright (c) 2017 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

namespace mk2{
namespace easing{

    struct quart_t
    {
        template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        constexpr T operator()(T normalized_time)
        {
            return normalized_time * normalized_time * normalized_time * normalized_time;
        }
    };

    static constexpr quart_t quart = quart_t{};

}
}
