//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <ipps.h>

#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp { namespace function {
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)      \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f##descriptor, Ipp32f)      \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f##descriptor, Ipp64f)      \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc##descriptor, Ipp32fc)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc##descriptor, Ipp64fc)
                
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    int order, int* pbuffer_size
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    order, pbuffer_size
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_iir_get_state_size, ippsIIRGetStateSize, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_iir_get_state_size_bi_quad, ippsIIRGetStateSize_BiQuad, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR
    
    
                
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)            \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f##descriptor, IppsIIRState_32f, Ipp32f)      \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f##descriptor, IppsIIRState_64f, Ipp64f)      \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc##descriptor, IppsIIRState_32fc, Ipp32fc)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc##descriptor, IppsIIRState_64fc, Ipp64fc)
                
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    IppsIIRState** ppstate, const Type* ptaps, int order, const Type* pdly_line, Ipp8u* pbuf
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    ppstate, ptaps, order, pdly_line, pbuf
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_iir_init, ippsIIRInit, , IppsIIRState, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_iir_init_bi_quad, ippsIIRInit_BiQuad, , IppsIIRState, Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const IppsIIRState* pstate, Type* pdly_line
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    pstate, pdly_line
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_iir_get_dly_line, ippsIIRGetDlyLine, , IppsIIRState, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_iir_set_dly_line, ippsIIRSetDlyLine, , IppsIIRState, Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    
    // not inplace
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type* pdst, int len, IppsIIRState* pstate
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len, pstate
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_iir, ippsIIR, , IppsIIRState, Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    // inplace
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    Type* psrc_dst, int len, IppsIIRState* pstate
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc_dst, len, pstate
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_iir_inplace, ippsIIR, _I, IppsIIRState, Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR
    
    
}}}}