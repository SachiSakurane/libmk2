//
// Created by Himatya on 2018-11-04.
//

#pragma once

#include <mk2/preprocessor/template_wrapper.hpp>
#include <mk2/simd/intrin/include.hpp>

namespace mk2 { namespace simd { namespace intrin { namespace wrapper { namespace intel {

    #define MK2_PP_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func)               \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_ps,       (__m128))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_pd,       (__m128d)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_ps,    (__m256))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_pd,    (__m256d)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_ps,    (__m512))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_pd,    (__m512d))

    MK2_PP_REPLACE_TO_TEMPLATE(add, add, (Type a, Type b), (a, b), (Type))
    MK2_PP_REPLACE_TO_TEMPLATE(sub, sub, (Type a, Type b), (a, b), (Type))
    MK2_PP_REPLACE_TO_TEMPLATE(div, div, (Type a, Type b), (a, b), (Type))
    MK2_PP_REPLACE_TO_TEMPLATE(mul, mul, (Type a, Type b), (a, b), (Type))

    #undef MK2_PP_REPLACE_TO_TEMPLATE_ASSOCIATOR

    #define MK2_PP_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func)               \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_ss,       (__m128))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_sd,       (__m128d)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_ss,    (__m256))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_sd,    (__m256d))

    MK2_PP_REPLACE_TO_TEMPLATE(add_ss, add, (Type a, Type b), (a, b), (Type))
    MK2_PP_REPLACE_TO_TEMPLATE(sub_ss, sub, (Type a, Type b), (a, b), (Type))
    MK2_PP_REPLACE_TO_TEMPLATE(div_ss, div, (Type a, Type b), (a, b), (Type))
    MK2_PP_REPLACE_TO_TEMPLATE(mul_ss, mul, (Type a, Type b), (a, b), (Type))

    #undef MK2_PP_REPLACE_TO_TEMPLATE_ASSOCIATOR

}}}}}