//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <mk2/simd/ipp/include.hpp>
#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp { namespace function {

#define MK2_SAMPLING_ASSOCIATOR(base_struct, base_func, name, desc)                         \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s,  name, desc), (Ipp16s))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f,  name, desc), (Ipp32f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f,  name, desc), (Ipp64f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16sc, name, desc), (Ipp16sc))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc, name, desc), (Ipp32fc))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc, name, desc), (Ipp64fc))

    MK2_IPP_REPLACE_TEMPLATE(sample_up, ippsSampleUp, , (const Type* psrc, int src_ln, Type* pdst, int* dst_len, int factor, int* pphase), (psrc, src_ln, pdst, dst_len, factor, pphase), (Type), MK2_SAMPLING_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(sample_down, ippsSampleDown, , (const Type* psrc, int src_ln, Type* pdst, int* dst_len, int factor, int* pphase), (psrc, src_ln, pdst, dst_len, factor, pphase), (Type), MK2_SAMPLING_ASSOCIATOR)

#undef MK2_SAMPLING_ASSOCIATOR

}}}}