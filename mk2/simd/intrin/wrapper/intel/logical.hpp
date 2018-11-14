//
// Created by Himatya on 2018-11-03.
//

#pragma once

#include <mk2/preprocessor/template_wrapper.hpp>
#include <mk2/simd/intrin/include.hpp>
#include <mk2/simd/intrin/utility/archtecture_requirement.hpp>

namespace mk2 { namespace simd { namespace intrin { namespace wrapper { namespace intel {

    #define MK2_LOGICAL_ASSOCIATOR(base_struct, base_func, ...)                                                                 \
    MK2_ARCHTECTURE_REQUIREMENT_SSE(     MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_ps,       (__m128)))    \
    MK2_ARCHTECTURE_REQUIREMENT_SSE2(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_pd,       (__m128d)))   \
    MK2_ARCHTECTURE_REQUIREMENT_SSE2(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_si128,    (__m128i)))   \
    MK2_ARCHTECTURE_REQUIREMENT_AVX(     MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_ps,    (__m256)))    \
    MK2_ARCHTECTURE_REQUIREMENT_AVX(     MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_pd,    (__m256d)))   \
    MK2_ARCHTECTURE_REQUIREMENT_AVX2(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_si256, (__m256i)))   \
    MK2_ARCHTECTURE_REQUIREMENT_AVX512DQ(MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_ps,    (__m512)))    \
    MK2_ARCHTECTURE_REQUIREMENT_AVX512DQ(MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_pd,    (__m512d)))   \
    MK2_ARCHTECTURE_REQUIREMENT_AVX512F( MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_si512, (__m512i)))

    MK2_PP_REPLACE_TO_TEMPLATE(bit_and,    and,    (Type a, Type b), (a, b), (Type), MK2_LOGICAL_ASSOCIATOR)
    MK2_PP_REPLACE_TO_TEMPLATE(bit_andnot, andnot, (Type a, Type b), (a, b), (Type), MK2_LOGICAL_ASSOCIATOR)
    MK2_PP_REPLACE_TO_TEMPLATE(bit_or,     or,     (Type a, Type b), (a, b), (Type), MK2_LOGICAL_ASSOCIATOR)
    MK2_PP_REPLACE_TO_TEMPLATE(bit_xor,    xor,    (Type a, Type b), (a, b), (Type), MK2_LOGICAL_ASSOCIATOR)

    #undef MK2_LOGICAL_ASSOCIATOR

    #define MK2_LOGICAL_TEST_ASSOCIATOR(base_struct, base_func, ...)                                                            \
    MK2_ARCHTECTURE_REQUIREMENT_SSE(     MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_ps,       (__m128)))    \
    MK2_ARCHTECTURE_REQUIREMENT_SSE2(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_pd,       (__m128d)))   \
    MK2_ARCHTECTURE_REQUIREMENT_SSE2(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_si128,    (__m128i)))   \
    MK2_ARCHTECTURE_REQUIREMENT_AVX(     MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_ps,    (__m256)))    \
    MK2_ARCHTECTURE_REQUIREMENT_AVX(     MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_pd,    (__m256d)))   \
    MK2_ARCHTECTURE_REQUIREMENT_AVX2(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_si256, (__m256i)))

    MK2_PP_REPLACE_TO_TEMPLATE(testc, testc, (Type a, Type b), (a, b), (Type), MK2_LOGICAL_TEST_ASSOCIATOR)
    MK2_PP_REPLACE_TO_TEMPLATE(testz, testz, (Type a, Type b), (a, b), (Type), MK2_LOGICAL_TEST_ASSOCIATOR)

    #undef MK2_LOGICAL_TEST_ASSOCIATOR

}}}}}