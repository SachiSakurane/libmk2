//
// Created by Himatya on 2018-11-03.
//

#pragma once

#include <mk2/simd/intrin/type_traits/architecture.hpp>
#include <mk2/simd/intrin/function/logical.hpp>

namespace mk2 { namespace simd { namespace intrin { namespace function {

    template <class Type>
    inline void swap(Type &a, Type &b)
    {
        a = mk2::simd::intrin::function::bit_xor(a, b);
        b = mk2::simd::intrin::function::bit_xor(a, b);
        a = mk2::simd::intrin::function::bit_xor(a, b);
    }

}}}}