//
// Created by Himatya on 2018-10-29.
//

#pragma once

#include <mk2/preprocessor/template_wrapper.hpp>
#include <mk2/simd/intrin/config.hpp>
#include <mk2/simd/intrin/include.hpp>

namespace mk2 { namespace simd { namespace intrin { namespace function {

    #define MK2_PP_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, r)                    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_ps, __m128, __m128)          \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_pd, __m128d, __m128d)        \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_si128, __m128i, __m128i)     \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_ps, __m256, __m256)       \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_pd, __m256d, __m256d)     \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_si256, __m256i, __m256i)  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_ps, __m512, __m512)       \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_pd, __m512d, __m512d)     \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_si512, __m512i, __m512i)

    MK2_PP_REPLACE_TO_TEMPLATE(setzero, setzero, Type, (), (), (Type))

    #undef MK2_PP_REPLACE_TO_TEMPLATE_ASSOCIATOR


}}}}