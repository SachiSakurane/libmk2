//
// Created by Himatya on 2018/08/17.
//

#pragma once

#include <ipp.h>

#include <mk2/simd/ipp/function/float_precision.h>
#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp { namespace function {
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC_ALL_PRECISION(base_struct, base_func, descriptor)            \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f_A11##descriptor, Ipp32f, precision_low) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f_A21##descriptor, Ipp32f, precision_mid) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f_A24##descriptor, Ipp32f, precision_high)\
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f_A26##descriptor, Ipp64f, precision_low) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f_A50##descriptor, Ipp64f, precision_mid) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f_A53##descriptor, Ipp64f, precision_high)
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC_ALL_PRECISION_COMPLEX(base_struct, base_func, descriptor)        \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc_A11##descriptor, Ipp32fc, precision_low)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc_A21##descriptor, Ipp32fc, precision_mid)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc_A24##descriptor, Ipp32fc, precision_high)  \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc_A26##descriptor, Ipp64fc, precision_low)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc_A50##descriptor, Ipp64fc, precision_mid)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc_A53##descriptor, Ipp64fc, precision_high)
    
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)             \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC_ALL_PRECISION(base_struct, base_func, descriptor)             \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC_ALL_PRECISION_COMPLEX(base_struct, base_func, descriptor)
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc1, const Type* psrc2, Type* pdst, int len, PrecisionType
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc1, psrc2, pdst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_pow, ippsPow, , Type, PrecisionType)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR
    
    
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f_A24##descriptor, Ipp32f, precision_high)\
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f_A53##descriptor, Ipp64f, precision_high)\
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC_ALL_PRECISION_COMPLEX(base_struct, base_func, descriptor)
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type* pdst, int len, PrecisionType
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_abs, ippsAbs, , Type, PrecisionType)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC_ALL_PRECISION
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC_ALL_PRECISION_COMPLEX
    
}}}}