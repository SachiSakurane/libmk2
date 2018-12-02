//
//  tanh.hpp
//
//
//  Created by Himatya on 2017/02/07.
//  Copyright (c) 2017 Himatya. All rights reserved.
//

#pragma once

#include <mk2/math/cosh.hpp>
#include <mk2/math/sinh.hpp>

namespace mk2{
namespace math{
    template<class T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T tanh(T x){
        return mk2::math::sinh(x) / mk2::math::cosh(x);
    }
}
}
