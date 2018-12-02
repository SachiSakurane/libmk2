//
//  theta_mod.hpp
//
//  Created by Himatya on 2015/12/20.
//  Copyright (c) 2015 Himatya. All rights reserved.
//

#pragma once

#include <mk2/math/mod.hpp>
#include <mk2/math/constants.hpp>

namespace mk2{
namespace math{
    template<class _T, typename = typename std::enable_if<std::is_floating_point<_T>::value>::type>
    inline constexpr _T theta_mod(_T x){
        return x < static_cast<_T>(0.0)
        ? math::two_pi<_T> + math::fmod(x, math::two_pi<_T>)
        : math::fmod(x, math::two_pi<_T>);
    }
}
}

