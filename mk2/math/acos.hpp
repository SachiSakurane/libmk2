//
//  acos.hpp
//
//
//  Created by Himatya on 2017/02/07.
//  Copyright (c) 2017 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

#include <mk2/math/asin.hpp>
#include <mk2/math/constants.hpp>

namespace mk2{ namespace math{
    template<class T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T acos(T x){
        return mk2::math::half_pi<T> - mk2::math::asin<T>(x);
    }
}
}