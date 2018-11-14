//
// Created by Himatya on 2018-11-04.
//

#pragma once

#include <mk2/preprocessor/template_wrapper.hpp>
#include <mk2/simd/intrin/include.hpp>
#include <mk2/simd/intrin/utility/archtecture_requirement.hpp>

namespace mk2 { namespace simd { namespace intrin { namespace wrapper { namespace intel {

    #define MK2_ARITHMETIC_ASSOCIATOR_AVX_LATER(base_struct, base_func)                                                     \
    MK2_ARCHTECTURE_REQUIREMENT_AVX(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_ps,    (__m256))) \
    MK2_ARCHTECTURE_REQUIREMENT_AVX(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_pd,    (__m256d)))\
    MK2_ARCHTECTURE_REQUIREMENT_AVX512F(MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_ps,    (__m512))) \
    MK2_ARCHTECTURE_REQUIREMENT_AVX512F(MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_pd,    (__m512d)))

    #define MK2_ARITHMETIC_ASSOCIATOR(base_struct, base_func, ...)                                                          \
    MK2_ARCHTECTURE_REQUIREMENT_SSE(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_ps,       (__m128))) \
    MK2_ARCHTECTURE_REQUIREMENT_SSE2(   MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_pd,       (__m128d)))\
    MK2_ARITHMETIC_ASSOCIATOR_AVX_LATER(base_struct, base_func)

    MK2_PP_REPLACE_TO_TEMPLATE(add, add, (RegisterType a, RegisterType b), (a, b), (RegisterType), MK2_ARITHMETIC_ASSOCIATOR)
    MK2_PP_REPLACE_TO_TEMPLATE(sub, sub, (RegisterType a, RegisterType b), (a, b), (RegisterType), MK2_ARITHMETIC_ASSOCIATOR)
    MK2_PP_REPLACE_TO_TEMPLATE(div, div, (RegisterType a, RegisterType b), (a, b), (RegisterType), MK2_ARITHMETIC_ASSOCIATOR)
    MK2_PP_REPLACE_TO_TEMPLATE(mul, mul, (RegisterType a, RegisterType b), (a, b), (RegisterType), MK2_ARITHMETIC_ASSOCIATOR)

    #undef MK2_ARITHMETIC_ASSOCIATOR

    #define MK2_ARITHMETIC_ADDSUB_ASSOCIATOR(base_struct, base_func, ...)                                                   \
    MK2_ARCHTECTURE_REQUIREMENT_SSE3(   MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_ps,       (__m128))) \
    MK2_ARCHTECTURE_REQUIREMENT_SSE3(   MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_pd,       (__m128d)))\
    MK2_ARITHMETIC_ASSOCIATOR_AVX_LATER(base_struct, base_func)

    MK2_PP_REPLACE_TO_TEMPLATE(addsub, addsub, (RegisterType a, RegisterType b), (a, b), (RegisterType), MK2_ARITHMETIC_ADDSUB_ASSOCIATOR)

    #undef MK2_ARITHMETIC_ADDSUB_ASSOCIATOR

    #define MK2_ARITHMETIC_S_ASSOCIATOR(base_struct, base_func, ...)                                                        \
    MK2_ARCHTECTURE_REQUIREMENT_SSE(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_ss,       (__m128))) \
    MK2_ARCHTECTURE_REQUIREMENT_SSE2(   MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_sd,       (__m128d)))\
    MK2_ARCHTECTURE_REQUIREMENT_AVX(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_ss,    (__m256))) \
    MK2_ARCHTECTURE_REQUIREMENT_AVX(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_sd,    (__m256d)))

    MK2_PP_REPLACE_TO_TEMPLATE(add_s, add, (RegisterType a, RegisterType b), (a, b), (RegisterType), MK2_ARITHMETIC_S_ASSOCIATOR)
    MK2_PP_REPLACE_TO_TEMPLATE(sub_s, sub, (RegisterType a, RegisterType b), (a, b), (RegisterType), MK2_ARITHMETIC_S_ASSOCIATOR)
    MK2_PP_REPLACE_TO_TEMPLATE(div_s, div, (RegisterType a, RegisterType b), (a, b), (RegisterType), MK2_ARITHMETIC_S_ASSOCIATOR)
    MK2_PP_REPLACE_TO_TEMPLATE(mul_s, mul, (RegisterType a, RegisterType b), (a, b), (RegisterType), MK2_ARITHMETIC_S_ASSOCIATOR)

    #undef MK2_ARITHMETIC_S_ASSOCIATOR

    // fma
    #define MK2_ARITHMETIC_FMA_ASSOCIATOR(base_struct, base_func, ...)                                                      \
    MK2_ARCHTECTURE_REQUIREMENT_FMA(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_ps,       (__m128))) \
    MK2_ARCHTECTURE_REQUIREMENT_FMA(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_pd,       (__m128d)))\
    MK2_ARCHTECTURE_REQUIREMENT_FMA(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_ps,    (__m256))) \
    MK2_ARCHTECTURE_REQUIREMENT_FMA(    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_pd,    (__m256d)))\
    MK2_ARCHTECTURE_REQUIREMENT_AVX512F(MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_ps,    (__m512))) \
    MK2_ARCHTECTURE_REQUIREMENT_AVX512F(MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_pd,    (__m512d)))

    MK2_PP_REPLACE_TO_TEMPLATE(fmadd, fmadd, (RegisterType a, RegisterType b, RegisterType c), (a, b, c), (RegisterType), MK2_ARITHMETIC_FMA_ASSOCIATOR)
    MK2_PP_REPLACE_TO_TEMPLATE(fmsub, fmsub, (RegisterType a, RegisterType b, RegisterType c), (a, b, c), (RegisterType), MK2_ARITHMETIC_FMA_ASSOCIATOR)
    MK2_PP_REPLACE_TO_TEMPLATE(fnmadd, fnmadd, (RegisterType a, RegisterType b, RegisterType c), (a, b, c), (RegisterType), MK2_ARITHMETIC_FMA_ASSOCIATOR)
    MK2_PP_REPLACE_TO_TEMPLATE(fnmsub, fnmsub, (RegisterType a, RegisterType b, RegisterType c), (a, b, c), (RegisterType), MK2_ARITHMETIC_FMA_ASSOCIATOR)
    MK2_PP_REPLACE_TO_TEMPLATE(fmaddsub, fmaddsub, (RegisterType a, RegisterType b, RegisterType c), (a, b, c), (RegisterType), MK2_ARITHMETIC_FMA_ASSOCIATOR)
    MK2_PP_REPLACE_TO_TEMPLATE(fmsubadd, fmsubadd, (RegisterType a, RegisterType b, RegisterType c), (a, b, c), (RegisterType), MK2_ARITHMETIC_FMA_ASSOCIATOR)

    #undef MK2_ARITHMETIC_FMA_ASSOCIATOR

}}}}}