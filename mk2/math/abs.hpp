//
//  abs.hpp
//  
//
//  Created by Himatya on 2015/12/20.
//  Copyright (c) 2015 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

namespace mk2{ namespace math{
    template<class _T, typename = typename std::enable_if<std::is_arithmetic<_T>::value>::type>
    inline constexpr _T abs(_T x)
    {
        return x < 0 ? -x : x;
    }
}
}