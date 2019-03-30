//
//  quadratic.hpp
//
//
//  Created by Himatya on 2017/02/09.
//  Copyright (c) 2017 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

namespace mk2{
namespace easing{

    struct quadratic_t
    {
        template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        constexpr T operator()(T normalized_time)
        {
            return normalized_time * normalized_time;
        }
    };

    static constexpr quadratic_t quadratic = quadratic_t{};

}
}

