//
// Created by Himatya on 2018/08/17.
//

#pragma once

#include <type_traits>

#include <ipps.h>

namespace mk2 { namespace simd { namespace ipp { namespace function {

    struct precision_high_t{};
    struct precision_mid_t{};
    struct precision_low_t{};
    
    static precision_high_t precision_high;
    static precision_mid_t precision_mid;
    static precision_low_t precision_low;
    
}}}}