//
// Created by Himatya on 2018-10-30.
//

#pragma once
#include <mk2/preprocessor/template_wrapper.hpp>
#include <mk2/simd/intrin/config.hpp>
#include <mk2/simd/intrin/include.hpp>
#include <mk2/simd/intrin/mm_type.hpp>

namespace mk2 { namespace simd { namespace intrin { namespace function {
    /*
    #define MK2_PP_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor, r)                \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_ps, __m128, const float*, m128)    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_pd, __m128d, const double*, m128)    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_ps, __m256, const float*, m256)         \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_pd, __m256d, const double*, m256)       \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_ps, __m512, const float*, m512)         \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_pd, __m512d, const double*, m512)

    #define MK2_PP_REPLACE_TO_TEMPLATE_SIGNATURE    \
    const Type* mem_addr

    #define MK2_PP_REPLACE_TO_TEMPLATE_ARGS \
    mem_addr

    MK2_PP_REPLACE_TO_TEMPLATE(load, load, , RetType, Type)

    #undef MK2_PP_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef MK2_PP_REPLACE_TO_TEMPLATE_ARGS

    #undef MK2_PP_REPLACE_TO_TEMPLATE_ASSOCIATOR
    */
}}}}