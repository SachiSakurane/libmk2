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

    struct back_t
    {
        template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        constexpr T operator()(T normalized_time)
        {
            return normalized_time * normalized_time * (static_cast<T>(2.70158) * normalized_time - static_cast<T>(1.70158));
        }
    };

    static constexpr back_t back = back_t{};

}
}
