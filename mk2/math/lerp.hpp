//
//  lerp.hpp
//
//
//  Created by Himatya on 2018/01/25.
//
//

#pragma once

#include <type_traits>

#include <mk2/algorithm/clamp.hpp>

namespace mk2{
namespace math{
    template<class Type, class FloatType, typename = typename std::enable_if<std::is_floating_point<FloatType>::value>::type>
    inline constexpr Type lerp(Type p1, Type p2, FloatType x)
    {
        return static_cast<Type>(p1 * x + p2 * (1 - x));
    }
    
    template<
        class Container,
        class FloatType,
        class ValueType = typename Container::value_type,
        class SizeType = typename Container::size_type,
        typename = typename std::enable_if<std::is_floating_point<FloatType>::value>::type
    >
    inline constexpr ValueType lerp(const Container& c, FloatType v)
    {
        v = mk2::algorithm::clamp(v, FloatType(0.0), FloatType(1.0));
        if(v == FloatType(1.0))
            return c[c.size() - 1];
        v *= c.size() - 1;
        SizeType v_pos = (SizeType)v;
        FloatType lerp = v - v_pos;
        return mk2::math::lerp(c[v_pos], c[v_pos + 1], lerp);
    }
}
}
