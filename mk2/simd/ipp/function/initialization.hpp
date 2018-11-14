//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <ipps.h>

#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp {
namespace function {

#define MK2_IPP_INITIALIZATION_ASSOCIATOR(base_struct, base_func, name, desc)               \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_8s, name, desc),   (Ipp8s))     \
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

    MK2_IPP_REPLACE_TEMPLATE(set, ippsSet, , (Type val, Type* pdst, int len), (val, pdst, len), (Type), MK2_IPP_INITIALIZATION_ASSOCIATOR)

    MK2_IPP_REPLACE_TEMPLATE(zero, ippsZero, , (Type* pdst, int len), (pdst, len), (Type), MK2_IPP_INITIALIZATION_ASSOCIATOR)

#undef MK2_IPP_INITIALIZATION_ASSOCIATOR

    /*
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_8s##descriptor, Ipp8s)      \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16s##descriptor, Ipp16s)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32s##descriptor, Ipp32s)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64s##descriptor, Ipp64s)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f##descriptor, Ipp32f)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f##descriptor, Ipp64f)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16sc##descriptor, Ipp16sc)  \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32sc##descriptor, Ipp32sc)  \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc##descriptor, Ipp32fc)  \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64sc##descriptor, Ipp64sc)  \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc##descriptor, Ipp64fc)
                
    // copy and move
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type* pdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len
                
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_copy, ippsCopy, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_move, ippsMove, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
                
    // set
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    Type val, Type* pdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    val, pdst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_set, ippsSet, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    // zero
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    Type* pdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    pdst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_zero, ippsZero, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
                
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR
     */
}}}}