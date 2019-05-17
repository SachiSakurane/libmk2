//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <mk2/simd/ipp/include.hpp>
#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp {
namespace function {

#define MK2_IPP_STATISTICAL_ASSOCIATOR(base_struct, base_func, name, desc)    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f, name, desc), (Ipp32f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f, name, desc), (Ipp64f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc, name, desc), (Ipp32fc))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc, name, desc), (Ipp64fc))

    MK2_IPP_REPLACE_TEMPLATE(sum, ippsSum, , (const Type* psrc, int len, Type* psum, IppHintAlgorithm hint), (psrc, len, psum, hint), (Type), MK2_IPP_STATISTICAL_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(mean, ippsMean, , (const Type* psrc, int len, Type* pmean, IppHintAlgorithm hint), (psrc, len, pmean, hint), (Type), MK2_IPP_STATISTICAL_ASSOCIATOR)

#undef MK2_IPP_STATISTICAL_ASSOCIATOR

#define MK2_IPP_STATISTICAL_DOT_PROD_ASSOCIATOR(base_struct, base_func, name, desc)                                 \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f,         name, desc), (Ipp32f,  Ipp32f,  Ipp32f))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc,        name, desc), (Ipp32fc, Ipp32fc, Ipp32fc))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f32fc,     name, desc), (Ipp32f,  Ipp32fc, Ipp32fc))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f64f,      name, desc), (Ipp32f,  Ipp32f,  Ipp64f))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc64fc,    name, desc), (Ipp32fc, Ipp32fc, Ipp64fc))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f32fc64fc, name, desc), (Ipp32f,  Ipp32fc, Ipp64fc))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f,         name, desc), (Ipp64f,  Ipp64f,  Ipp64f))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc,        name, desc), (Ipp64fc, Ipp64fc, Ipp64fc))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f64fc,     name, desc), (Ipp64f,  Ipp64fc, Ipp64fc))

    MK2_IPP_REPLACE_TEMPLATE(dot_prod, ippsDotProd, , (const Type1* psrc1, const Type2* psrc2, int len, Type3* pdp), (psrc1, psrc2, len, pdp), (Type1, Type2, Type3), MK2_IPP_STATISTICAL_DOT_PROD_ASSOCIATOR)

#undef MK2_IPP_STATISTICAL_DOT_PROD_ASSOCIATOR

#define MK2_IPP_STATISTICAL_MAX_MIN_ASSOCIATOR(base_struct, base_func, name, desc)      \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s, name, desc), (Ipp16s)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32s, name, desc), (Ipp32s)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f, name, desc), (Ipp32f)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f, name, desc), (Ipp64f))

    MK2_IPP_REPLACE_TEMPLATE(max, ippsMax, , (const Type* psrc, int len, Type* pdst), (psrc, len, pdst), (Type), MK2_IPP_STATISTICAL_MAX_MIN_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(min, ippsMin, , (const Type* psrc, int len, Type* pdst), (psrc, len, pdst), (Type), MK2_IPP_STATISTICAL_MAX_MIN_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(max_index, ippsMaxIndx, , (const Type* psrc, int len, Type* pmax, int* pindex), (psrc, len, pmax, pindex), (Type), MK2_IPP_STATISTICAL_MAX_MIN_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(min_index, ippsMinIndx, , (const Type* psrc, int len, Type* pmin, int* pindex), (psrc, len, pmin, pindex), (Type), MK2_IPP_STATISTICAL_MAX_MIN_ASSOCIATOR)

    MK2_IPP_REPLACE_TEMPLATE(max_abs, ippsMaxAbs, , (const Type* psrc, int len, Type* pmax_abs), (psrc, len, pmax_abs), (Type), MK2_IPP_STATISTICAL_MAX_MIN_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(min_abs, ippsMinAbs, , (const Type* psrc, int len, Type* pmin_abs), (psrc, len, pmin_abs), (Type), MK2_IPP_STATISTICAL_MAX_MIN_ASSOCIATOR)

#undef MK2_IPP_STATISTICAL_MAX_MIN_ASSOCIATOR

#define MK2_IPP_STATISTICAL_MAX_MIN_ASSOCIATOR_2(base_struct, base_func, name, desc)    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_8u, name, desc), (Ipp8u))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16u, name, desc), (Ipp16u)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s, name, desc), (Ipp16s)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32u, name, desc), (Ipp32u)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32s, name, desc), (Ipp32s)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f, name, desc), (Ipp32f)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f, name, desc), (Ipp64f))

    MK2_IPP_REPLACE_TEMPLATE(min_max, ippsMinMax, , (const Type* psrc, int len, Type* pmin, Type* pmax), (psrc, len, pmin, pmax), (Type), MK2_IPP_STATISTICAL_MAX_MIN_ASSOCIATOR_2)
    MK2_IPP_REPLACE_TEMPLATE(min_max_index, ippsMinMaxIndx, , (const Type* psrc, int len, Type* pmin, int* pmin_index, Type* pmax, int* pmax_index), (psrc, len, pmin, pmin_index, pmax, pmax_index), (Type), MK2_IPP_STATISTICAL_MAX_MIN_ASSOCIATOR_2)

#undef MK2_IPP_STATISTICAL_MAX_MIN_ASSOCIATOR_2

#define MK2_IPP_STATISTICAL_MAX_MIN_EVERY_ASSOCIATOR(base_struct, base_func, name, desc) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_8u,  name, desc), (Ipp8u))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16u, name, desc), (Ipp16u))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f, name, desc), (Ipp32f))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f, name, desc), (Ipp64f))
    
    MK2_IPP_REPLACE_TEMPLATE(max_every, ippsMaxEvery, , (const Type* psrc1, const Type* psrc2, Type* pdst, Ipp32u len), (psrc1, psrc2, pdst, len), (Type), MK2_IPP_STATISTICAL_MAX_MIN_EVERY_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(min_every, ippsMinEvery, , (const Type* psrc1, const Type* psrc2, Type* pdst, Ipp32u len), (psrc1, psrc2, pdst, len), (Type), MK2_IPP_STATISTICAL_MAX_MIN_EVERY_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(max_every_inplace, ippsMaxEvery, _I, (const Type* psrc, Type* psrcdst, int len), (psrc, psrcdst, len), (Type), MK2_IPP_STATISTICAL_MAX_MIN_EVERY_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(min_every_inplace, ippsMinEvery, _I, (const Type* psrc, Type* psrcdst, int len), (psrc, psrcdst, len), (Type), MK2_IPP_STATISTICAL_MAX_MIN_EVERY_ASSOCIATOR)

#undef MK2_IPP_STATISTICAL_MAX_MIN_EVERY_ASSOCIATOR    
    
}}}}