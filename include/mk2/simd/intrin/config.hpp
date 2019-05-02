//
// Created by Himatya on 2018-10-28.
//

#pragma once

#include <boost/preprocessor.hpp>

#include <mk2/simd/intrin/include.hpp>

#ifdef __AVX512F__
#   define MK2_INTRIN_ENABLE_AVX512F 1
#else
#   define MK2_INTRIN_ENABLE_AVX512F 0
#endif

#if MK2_INTRIN_ENABLE_AVX512F
#   define MK2_IF_AVX512F(x) BOOST_PP_TUPLE_ELEM(0, x)
#else
#   define MK2_IF_AVX512F(x)
#endif

#define MK2_INTRIN_ALGORITHM_SWITCH_THRESHOLD 1024