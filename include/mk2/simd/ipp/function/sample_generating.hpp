//
// Created by Himatya on 2018/09/09.
//

#pragma once

#include <mk2/simd/ipp/include.hpp>
#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp {
namespace function {

#define MK2_SAMPLE_GENERATING_ASSOCIATOR(base_struct, base_func, name, desc)                    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_8u,  name, desc), (Ipp8u, Ipp32f))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16u, name, desc), (Ipp16u, Ipp32f)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s, name, desc), (Ipp16s, Ipp32f)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32u, name, desc), (Ipp32u, Ipp64f)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32s, name, desc), (Ipp32s, Ipp64f)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f, name, desc), (Ipp32f, Ipp32f)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f, name, desc), (Ipp64f, Ipp64f))

    MK2_IPP_REPLACE_TEMPLATE(vector_slope, ippsVectorSlope, , (Type1* pdst, int len, Type2 offset, Type2 slope), (pdst, len, offset, slope), (Type1, Type2), MK2_SAMPLE_GENERATING_ASSOCIATOR)

#undef MK2_SAMPLE_GENERATING_ASSOCIATOR

}}}}