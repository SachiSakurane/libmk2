//
//  sin.hpp
//
//
//  Created by Himatya on 2015/12/18.
//  Copyright (c) 2015 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

#include <mk2/math/cos.hpp>

namespace mk2{
namespace math{
    template<class T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T sin(T x){
        return cos(x - math::half_pi<T>);
    }
}
}
