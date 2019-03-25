//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <ipps.h>

#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp {
namespace function {

#define MK2_IPP_INITIALIZATION_ASSOCIATOR(base_struct, base_func, name, desc)               \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_8u, name, desc),   (Ipp8u))     \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s, name, desc),  (Ipp16s))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32s, name, desc),  (Ipp32s))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64s, name, desc),  (Ipp64s))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f, name, desc),  (Ipp32f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f, name, desc),  (Ipp64f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16sc, name, desc), (Ipp16sc))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32sc, name, desc), (Ipp32sc))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc, name, desc), (Ipp32fc))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64sc, name, desc), (Ipp64sc))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc, name, desc), (Ipp64fc))

    MK2_IPP_REPLACE_TEMPLATE(copy, ippsCopy, , (const Type* psrc, Type* pdst, int len), (psrc, pdst, len), (Type), MK2_IPP_INITIALIZATION_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(move, ippsMove, , (const Type* psrc, Type* pdst, int len), (psrc, pdst, len), (Type), MK2_IPP_INITIALIZATION_ASSOCIATOR)

    MK2_IPP_REPLACE_TEMPLATE(set,  ippsSet,  , (Type val, Type* pdst, int len), (val, pdst, len), (Type), MK2_IPP_INITIALIZATION_ASSOCIATOR)

    MK2_IPP_REPLACE_TEMPLATE(zero, ippsZero, , (Type* pdst, int len), (pdst, len), (Type), MK2_IPP_INITIALIZATION_ASSOCIATOR)

#undef MK2_IPP_INITIALIZATION_ASSOCIATOR

}}}}