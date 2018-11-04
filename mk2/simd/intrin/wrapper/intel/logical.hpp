//
// Created by Himatya on 2018-11-03.
//

#pragma once

#include <mk2/preprocessor/template_wrapper.hpp>
#include <mk2/simd/intrin/include.hpp>

namespace mk2 { namespace simd { namespace intrin { namespace wrapper { namespace intel {

    #define MK2_PP_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func)               \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_ps,       (__m128))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_pd,       (__m128d)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_si128,    (__m128i)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_ps,    (__m256))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_pd,    (__m256d)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_si256, (__m256i)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_ps,    (__m512))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_pd,    (__m512d)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_si512, (__m512i))

    MK2_PP_REPLACE_TO_TEMPLATE(bit_and, and, (Type a, Type b), (a, b), (Type))
    MK2_PP_REPLACE_TO_TEMPLATE(bit_andnot, andnot, (Type a, Type b), (a, b), (Type))
    MK2_PP_REPLACE_TO_TEMPLATE(bit_or, or, (Type a, Type b), (a, b), (Type))
    MK2_PP_REPLACE_TO_TEMPLATE(bit_xor, xor, (Type a, Type b), (a, b), (Type))

    #undef MK2_PP_REPLACE_TO_TEMPLATE_ASSOCIATOR

    #define MK2_PP_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func)               \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_ps,       (__m128))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_pd,       (__m128d)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_si128,    (__m128i)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_ps,    (__m256))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_pd,    (__m256d)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_si256, (__m256i))

    MK2_PP_REPLACE_TO_TEMPLATE(testc, testc, (Type a, Type b), (a, b), (Type))
    MK2_PP_REPLACE_TO_TEMPLATE(testz, testz, (Type a, Type b), (a, b), (Type))

    #undef MK2_PP_REPLACE_TO_TEMPLATE_ASSOCIATOR

}}}}}