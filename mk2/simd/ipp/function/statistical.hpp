//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <ipps.h>

#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp {
namespace function {

#define MK2_IPP_STATISTICAL_ASSOCIATOR(base_struct, base_func, name, desc)    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f, name, desc), (Ipp32f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f, name, desc), (Ipp64f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc, name, desc), (Ipp32fc))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc, name, desc), (Ipp64fc))

    MK2_IPP_REPLACE_TEMPLATE(sum, ippsSum, , (const Type* psrc, int len, Type* psum, IppHintAlgorithm hint), (psrc, len, psum, hint), (Type), MK2_IPP_STATISTICAL_ASSOCIATOR)

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
    MK2_IPP_REPLACE_TEMPLATE(min_max, ippsMinMax, , (const Type* psrc, int len, Type* pmin, Type* pmax), (psrc, len, pmin, pmax), (Type), MK2_IPP_STATISTICAL_MAX_MIN_ASSOCIATOR)

#undef MK2_IPP_STATISTICAL_MAX_MIN_ASSOCIATOR

    /*
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f##descriptor, Ipp32f)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f##descriptor, Ipp64f)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc##descriptor, Ipp32fc)  \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc##descriptor, Ipp64fc)
    
    // not inplace
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, int len, Type* psum, IppHintAlgorithm hint
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, len, psum, hint
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_sum, ippsSum, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR

    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)                            \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f##descriptor, Ipp32f, Ipp32f, Ipp32f)            \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc##descriptor, Ipp32fc, Ipp32fc, Ipp32fc)        \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f32fc##descriptor, Ipp32f, Ipp32fc, Ipp32fc)      \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f64f##descriptor, Ipp32f, Ipp32f, Ipp64f)         \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc64fc##descriptor, Ipp32fc, Ipp32fc, Ipp64fc)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f32fc64fc##descriptor, Ipp32f, Ipp32fc, Ipp64fc)  \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f##descriptor, Ipp64f, Ipp64f, Ipp64f)            \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc##descriptor, Ipp64fc, Ipp64fc, Ipp64fc)        \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f64fc##descriptor, Ipp64f, Ipp64fc, Ipp64fc)
    
    // not inplace
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type1* psrc1, const Type2* psrc2, int len, Type3* pdp
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc1, psrc2, len, pdp
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_dot_prod, ippsDotProd, , Type1, Type2, Type3)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR
    */
    /*
    // max min
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16s##descriptor, Ipp16s)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32s##descriptor, Ipp32s)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f##descriptor, Ipp32f)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f##descriptor, Ipp64f)
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, int len, Type* pdst
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, len, pdst
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_max, ippsMax, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_min, ippsMin, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
                
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, int len, Type* pmin, Type* pmax
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, len, pmin, pmax
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_min_max, ippsMinMax, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
                
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR
    */
}}}}