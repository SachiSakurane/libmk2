//
// Created by Himatya on 2018-10-29.
//

#pragma once

#include <mk2/preprocessor/template_wrapper.hpp>
#include <mk2/simd/intrin/include.hpp>
#include <mk2/simd/intrin/type_traits/bit_type.hpp>
#include <mk2/simd/intrin/utility/archtecture_requirement.hpp>

namespace mk2 { namespace simd { namespace intrin { namespace wrapper { namespace intel {

    #define MK2_SET_ASSOCIATOR(base_struct, base_func, ...)                                                                         \
    MK2_ARCHTECTURE_REQUIREMENT_SSE(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_ps,       (m128, float)))    \
    MK2_ARCHTECTURE_REQUIREMENT_SSE2(   MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_pd,       (m128, double)))   \
    MK2_ARCHTECTURE_REQUIREMENT_SSE2(   MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_si128,    (m128, int)))      \
    MK2_ARCHTECTURE_REQUIREMENT_AVX(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_ps,    (m256, float)))    \
    MK2_ARCHTECTURE_REQUIREMENT_AVX(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_pd,    (m256, double)))   \
    MK2_ARCHTECTURE_REQUIREMENT_AVX(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_si256, (m256, int)))      \
    MK2_ARCHTECTURE_REQUIREMENT_AVX512F(MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_ps,    (m512, float)))    \
    MK2_ARCHTECTURE_REQUIREMENT_AVX512F(MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_pd,    (m512, double)))   \
    MK2_ARCHTECTURE_REQUIREMENT_AVX512F(MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_si512, (m512, int)))

    MK2_PP_REPLACE_TO_TEMPLATE(setzero, setzero, (), (), (Bit, Type), MK2_SET_ASSOCIATOR)

    #undef MK2_SET_ASSOCIATOR

    // set set1
    #define MK2_SET1_ASSOCIATOR(base_struct, base_func, ...)                                                                        \
    MK2_ARCHTECTURE_REQUIREMENT_SSE(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_ps,       (m128, float)))    \
    MK2_ARCHTECTURE_REQUIREMENT_SSE2(   MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_pd,       (m128, double)))   \
    MK2_ARCHTECTURE_REQUIREMENT_AVX(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_ps,    (m256, float)))    \
    MK2_ARCHTECTURE_REQUIREMENT_AVX(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_pd,    (m256, double)))   \
    MK2_ARCHTECTURE_REQUIREMENT_AVX512F(MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_ps,    (m512, float)))    \
    MK2_ARCHTECTURE_REQUIREMENT_AVX512F(MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_pd,    (m512, double)))

    MK2_PP_REPLACE_TO_TEMPLATE(set1, set1, (Type a), (a), (Bit, Type), MK2_SET1_ASSOCIATOR)

    #undef MK2_SET1_ASSOCIATOR

}}}}}