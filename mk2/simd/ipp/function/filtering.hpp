//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <ipps.h>

#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp {
namespace function {

#define MK2_IPP_FILTERING_GET_STATE_SIZE_ASSOCIATOR(base_struct, base_func, name, desc)     \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f,  name, desc), (Ipp32f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f,  name, desc), (Ipp64f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc, name, desc), (Ipp32fc))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc, name, desc), (Ipp64fc))

    MK2_IPP_REPLACE_TEMPLATE(iir_get_state_size, ippsIIRGetStateSize, , (int order, int* pbuffer_size), (order, pbuffer_size), (Type), MK2_IPP_FILTERING_GET_STATE_SIZE_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(iir_get_state_size_bi_quad, ippsIIRGetStateSize_BiQuad, , (int order, int* pbuffer_size), (order, pbuffer_size), (Type), MK2_IPP_FILTERING_GET_STATE_SIZE_ASSOCIATOR)

#define MK2_IPP_IIR_FILTERING_ASSOCIATOR(base_struct, base_func, name, desc)                                \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f,  name, desc), (IppsIIRState_32f, Ipp32f))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f,  name, desc), (IppsIIRState_64f, Ipp64f))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc, name, desc), (IppsIIRState_32fc, Ipp32fc))\
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc, name, desc), (IppsIIRState_64fc, Ipp64fc))

    MK2_IPP_REPLACE_TEMPLATE(iir_init, ippsIIRInit, , (IppsIIRState** ppstate, const Type* ptaps, int order, const Type* pdly_line, Ipp8u* pbuf), (ppstate, ptaps, order, pdly_line, pbuf), (IppsIIRState, Type), MK2_IPP_IIR_FILTERING_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(iir_init_bi_quad, ippsIIRInit_BiQuad, , (IppsIIRState** ppstate, const Type* ptaps, int order, const Type* pdly_line, Ipp8u* pbuf), (ppstate, ptaps, order, pdly_line, pbuf), (IppsIIRState, Type), MK2_IPP_IIR_FILTERING_ASSOCIATOR)

    MK2_IPP_REPLACE_TEMPLATE(ipps_iir_get_dly_line, ippsIIRGetDlyLine, , (const IppsIIRState* pstate, Type* pdly_line), (pstate, pdly_line), (IppsIIRState, Type), MK2_IPP_IIR_FILTERING_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(ipps_iir_set_dly_line, ippsIIRSetDlyLine, , (const IppsIIRState* pstate, Type* pdly_line), (pstate, pdly_line), (IppsIIRState, Type), MK2_IPP_IIR_FILTERING_ASSOCIATOR)

    // iir
    MK2_IPP_REPLACE_TEMPLATE(iir, ippsIIR, , (const Type* psrc, Type* pdst, int len, IppsIIRState* pstate), (psrc, pdst, len, pstate), (IppsIIRState, Type), MK2_IPP_IIR_FILTERING_ASSOCIATOR)

    // iir inplace
    MK2_IPP_REPLACE_TEMPLATE(iir_inplace, ippsIIR, _I, (Type* psrc_dst, int len, IppsIIRState* pstate), (psrc_dst, len, pstate), (IppsIIRState, Type), MK2_IPP_IIR_FILTERING_ASSOCIATOR)

#undef MK2_IPP_FILTERING_GET_STATE_SIZE_ASSOCIATOR
#undef MK2_IPP_IIR_FILTERING_ASSOCIATOR

#define MK2_IPP_FIR_FILTERING_ASSOCIATOR(base_struct, base_func, name, desc)                               \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f,  name, desc), (IppsFIRSpec_32f, Ipp32f))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f,  name, desc), (IppsFIRSpec_64f, Ipp64f))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc, name, desc), (IppsFIRSpec_32fc, Ipp32fc))\
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc, name, desc), (IppsFIRSpec_64fc, Ipp64fc))

    // SR
    MK2_IPP_REPLACE_TEMPLATE(fir_sr_init, ippsFIRSRInit, , (const Type* ptaps, int taps_len, IppAlgType alg_type, IppsFIRSpec* pspec), (ptaps, taps_len, alg_type, pspec), (Type, IppsFIRSpec), MK2_IPP_FIR_FILTERING_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(fir_sr, ippsFIRSR, , (const Type* psrc, Type* pdst, int num_iters, IppsFIRSpec* pspec, const Type* pdly_src, Type* pdly_dst, Ipp8u* pbuf), (psrc, pdst, num_iters, pspec, pdly_src, pdly_dst, pbuf), (Type, IppsFIRSpec), MK2_IPP_FIR_FILTERING_ASSOCIATOR)


#undef MK2_IPP_FIR_FILTERING_ASSOCIATOR
}}}}