//
//  tan.hpp
//
//
//  Created by Himatya on 2016/11/20.
//
//

#pragma once

#include <type_traits>

#include <mk2/math/cos.hpp>
#include <mk2/math/sin.hpp>

namespace mk2{
namespace math{
    template<class T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T tan(T x){
        return sin(x) / cos(x);
    }
}
}
