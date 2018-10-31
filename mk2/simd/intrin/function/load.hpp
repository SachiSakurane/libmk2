//
// Created by Himatya on 2018-10-30.
//

#pragma once

#include <mk2/preprocessor/template_wrapper.hpp>
#include <mk2/simd/intrin/alignment.hpp>
#include <mk2/simd/intrin/config.hpp>
#include <mk2/simd/intrin/include.hpp>
#include <mk2/simd/intrin/mm_type.hpp>

namespace mk2 { namespace simd { namespace intrin { namespace function {

    #define MK2_PP_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func)                                                       \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_ps,     (m128, float,  mk2::simd::intrin::is_aligned<true>)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##_pd,     (m128, double, mk2::simd::intrin::is_aligned<true>)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_ps,  (m256, float,  mk2::simd::intrin::is_aligned<true>)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##_pd,  (m256, double, mk2::simd::intrin::is_aligned<true>)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_ps,  (m512, float,  mk2::simd::intrin::is_aligned<true>)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##_pd,  (m512, double, mk2::simd::intrin::is_aligned<true>)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##u_ps,    (m128, float,  mk2::simd::intrin::is_aligned<false>))\
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm_##base_func##u_pd,    (m128, double, mk2::simd::intrin::is_aligned<false>))\
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##u_ps, (m256, float,  mk2::simd::intrin::is_aligned<false>))\
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm256_##base_func##u_pd, (m256, double, mk2::simd::intrin::is_aligned<false>))\
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##u_ps, (m512, float,  mk2::simd::intrin::is_aligned<false>))\
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, _mm512_##base_func##u_pd, (m512, double, mk2::simd::intrin::is_aligned<false>))

    MK2_PP_REPLACE_TO_TEMPLATE(load, load, (const Type* mem_addr), (mem_addr), (RegisterType, Type, IsAligned))
    MK2_PP_REPLACE_TO_TEMPLATE(store, store, (Type* mem_addr, RegisterType r), (mem_addr, r), (RegisterType, Type, IsAligned))

    #undef MK2_PP_REPLACE_TO_TEMPLATE_ASSOCIATOR

}}}}