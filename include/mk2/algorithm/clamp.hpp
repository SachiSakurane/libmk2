//
// Created by Himatya on 2018/01/25.
//

#pragma once

namespace mk2{
namespace algorithm{
    template<class T>
    constexpr const T& clamp(const T& v, const T& lo, const T& hi)
    {
        return v < lo ? lo : v > hi ? hi : v;
    }
}
}
