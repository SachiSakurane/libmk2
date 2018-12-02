//
//  mod.hpp
//
//
//  Created by Himatya on 2015/12/20.
//  Copyright (c) 2015 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

#include <mk2/math/abs.hpp>

namespace mk2{
namespace math{
    template<class _T, typename = typename std::enable_if<std::is_floating_point<_T>::value>::type>
    inline constexpr _T fmod(_T x, _T y){
        return x - static_cast<_T>(static_cast<unsigned long long int>(math::abs(x / y))) * y;
    }
    
}
}
