//
// Created by Himatya on 2018/08/21.
//

#pragma once


#include <ipps.h>

#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp { namespace function {
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_8u##descriptor, Ipp8u)      \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16u##descriptor, Ipp16u)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32u##descriptor, Ipp32u)
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc1, const Type* psrc2, Type* pdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc1, psrc2, pdst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_and, ippsAnd, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_or, ippsOr, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_xor, ippsXor, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type* psrcdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, psrcdst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_and_inplace, ippsAnd, _I, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_or_inplace, ippsOr, _I, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_xor_inplace, ippsXor, _I, Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    // c
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type val, Type* pdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, val, pdst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_andc, ippsAnd, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_orc, ippsOr, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_xorc, ippsXor, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    Type val, Type* pdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    val, pdst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_andc_inplace, ippsAnd, _I, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_orc_inplace, ippsOr, _I, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_xorc_inplace, ippsXor, _I, Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    // not
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type* pdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_not, ippsNot, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type* pdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_not_inplace, ippsNot, _I, Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR

}}}}