//
// Created by Himatya on 2018-10-30.
//

#pragma once

#include <mk2/preprocessor/template_wrapper.hpp>
#include <mk2/simd/intrin/type_traits/alignment.hpp>
#include <mk2/simd/intrin/type_traits/bit_type.hpp>
#include <mk2/simd/intrin/config.hpp>
#include <mk2/simd/intrin/include.hpp>

namespace mk2 { namespace simd { namespace intrin { namespace function {

    #define MK2_PP_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func)                               \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_ps,     (m128, float,  aligned))     \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_pd,     (m128, double, aligned))     \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_ps,  (m256, float,  aligned))     \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_pd,  (m256, double, aligned))     \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_ps,  (m512, float,  aligned))     \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_pd,  (m512, double, aligned))     \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##u_ps,    (m128, float,  not_aligned)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##u_pd,    (m128, double, not_aligned)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##u_ps, (m256, float,  not_aligned)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##u_pd, (m256, double, not_aligned)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##u_ps, (m512, float,  not_aligned)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##u_pd, (m512, double, not_aligned))

    MK2_PP_REPLACE_TO_TEMPLATE_REDUNDANCY(
            load, load,
            (const Type* mem_addr), (mem_addr),
            (Bit, Type, Align), (Bit, Type, Align = aligned))

    MK2_PP_REPLACE_TO_TEMPLATE_REDUNDANCY(
            store, store,
            (Type* mem_addr, typename bit_type<Type, Bit>::type r), (mem_addr, r),
            (Bit, Type, Align), (Bit, Type, Align = aligned))

    #undef MK2_PP_REPLACE_TO_TEMPLATE_ASSOCIATOR

}}}}