//
// Created by Himatya on 2018-10-31.
//

#pragma once

#include <traits>

namespace mk2 { namespace simd { namespace intrin {
    template<Bool B> struct is_aligned<B>
    {
        static constexpr bool value = B;
    }
    
}}}