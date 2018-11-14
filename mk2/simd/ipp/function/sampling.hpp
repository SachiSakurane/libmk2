//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <ipps.h>

#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp { namespace function {

#define MK2_SAMPLING_ASSOCIATOR(base_struct, base_func, name, desc)                         \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s,  name, desc), (Ipp16s))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f,  name, desc), (Ipp32f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f,  name, desc), (Ipp64f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc, name, desc), (Ipp32fc))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc, name, desc), (Ipp64fc))

    MK2_IPP_REPLACE_TEMPLATE(sample_up, ippsSampleUp, , (const Type* psrc, int src_ln, Type* pdst, int* dst_len, int factor, int* pphase), (psrc, src_ln, pdst, dst_len, factor, pphase), (Type), MK2_SAMPLING_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(sample_down, ippsSampleDown, , (const Type* psrc, int src_ln, Type* pdst, int* dst_len, int factor, int* pphase), (psrc, src_ln, pdst, dst_len, factor, pphase), (Type), MK2_SAMPLING_ASSOCIATOR)

#undef MK2_SAMPLING_ASSOCIATOR

    /*
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)      \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16s##descriptor, Ipp16s)      \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f##descriptor, Ipp32f)      \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f##descriptor, Ipp64f)      \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc##descriptor, Ipp32fc)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc##descriptor, Ipp64fc)
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, int src_ln, Type* pdst, int* dst_len, int factor, int* pphase
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, src_ln, pdst, dst_len, factor, pphase
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_sample_up, ippsSampleUp, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_sample_down, ippsSampleDown, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR
    */
}}}}