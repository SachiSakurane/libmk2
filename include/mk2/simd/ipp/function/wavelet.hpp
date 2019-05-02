//
// Created by Himatya on 2018-12-05.
//

#pragma once

#include <ipps.h>

#include <mk2/preprocessor/template_wrapper.hpp>
#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp {
namespace function {

#define MK2_IPP_WT_FWD_ASSOCIATOR(base_struct, base_func, name, desc)                                       \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f,    name, desc), (IppsWTFwdState_32f))      \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_8u32f,  name, desc), (IppsWTFwdState_8u32f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s32f, name, desc), (IppsWTFwdState_16s32f))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16u32f, name, desc), (IppsWTFwdState_16u32f))

#define MK2_IPP_WT_INV_ASSOCIATOR(base_struct, base_func, name, desc)                                       \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f,    name, desc), (IppsWTInvState_32f))      \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f8u,  name, desc), (IppsWTInvState_32f8u))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f16s, name, desc), (IppsWTInvState_32f16s))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f16u, name, desc), (IppsWTInvState_32f16u))

#define MK2_IPP_WT_INIT_ARITHMETIC_SIGNATURE    (IppsWTState* pstate, const Ipp32f* ptaps_low, int len_low, int offs_low, const Ipp32f* ptaps_high, int len_high, int offs_high)
#define MK2_IPP_WT_INIT_ARITHMETIC_ARGS         (pstate, ptaps_low, len_low, offs_low, ptaps_high, len_high, offs_high)

    MK2_IPP_REPLACE_TEMPLATE(wt_fwd_init, ippsWTFwdInit, , MK2_IPP_WT_INIT_ARITHMETIC_SIGNATURE, MK2_IPP_WT_INIT_ARITHMETIC_ARGS, (IppsWTState), MK2_IPP_WT_FWD_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(wt_inv_init, ippsWTInvInit, , MK2_IPP_WT_INIT_ARITHMETIC_SIGNATURE, MK2_IPP_WT_INIT_ARITHMETIC_ARGS, (IppsWTState), MK2_IPP_WT_INV_ASSOCIATOR)

#undef MK2_IPP_WT_INIT_ARITHMETIC_SIGNATURE
#undef MK2_IPP_WT_INIT_ARITHMETIC_ARGS

#define MK2_IPP_WT_DLY_LINE_ARITHMETIC_SIGNATURE    (IppsWTState* pstate, const Ipp32f* pdly_low, const Ipp32f* pdly_high)
#define MK2_IPP_WT_DLY_LINE_ARITHMETIC_ARGS         (pstate, pdly_low, pdly_high)

    MK2_IPP_REPLACE_TEMPLATE(wt_fwd_set_dly_line, ippsWTFwdSetDlyLine_32f, , MK2_IPP_WT_DLY_LINE_ARITHMETIC_SIGNATURE, MK2_IPP_WT_DLY_LINE_ARITHMETIC_ARGS, (IppsWTState), MK2_IPP_WT_FWD_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(wt_fwd_get_dly_line, ippsWTFwdGetDlyLine_32f, , MK2_IPP_WT_DLY_LINE_ARITHMETIC_SIGNATURE, MK2_IPP_WT_DLY_LINE_ARITHMETIC_ARGS, (IppsWTState), MK2_IPP_WT_FWD_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(wt_inv_set_dly_line, ippsWTInvSetDlyLine_32f, , MK2_IPP_WT_DLY_LINE_ARITHMETIC_SIGNATURE, MK2_IPP_WT_DLY_LINE_ARITHMETIC_ARGS, (IppsWTState), MK2_IPP_WT_INV_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(wt_inv_get_dly_line, ippsWTInvGetDlyLine_32f, , MK2_IPP_WT_DLY_LINE_ARITHMETIC_SIGNATURE, MK2_IPP_WT_DLY_LINE_ARITHMETIC_ARGS, (IppsWTState), MK2_IPP_WT_INV_ASSOCIATOR)


#undef MK2_IPP_WT_DLY_LINE_ARITHMETIC_SIGNATURE
#undef MK2_IPP_WT_DLY_LINE_ARITHMETIC_ARGS

#define MK2_IPP_WT_FWD_ASSOCIATOR_2(base_struct, base_func, name, desc)                                               \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f,    name, desc), (IppsWTFwdState_32f,    Ipp32f))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_8u32f,  name, desc), (IppsWTFwdState_8u32f,  Ipp8u))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s32f, name, desc), (IppsWTFwdState_16s32f, Ipp16s))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16u32f, name, desc), (IppsWTFwdState_16u32f, Ipp16u))

#define MK2_IPP_WT_INV_ASSOCIATOR_2(base_struct, base_func, name, desc)                                               \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f,    name, desc), (IppsWTInvState_32f,    Ipp32f))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f8u,  name, desc), (IppsWTInvState_32f8u,  Ipp8u))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f16s, name, desc), (IppsWTInvState_32f16s, Ipp16s))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f16u, name, desc), (IppsWTInvState_32f16u, Ipp16u))

    MK2_IPP_REPLACE_TEMPLATE(wt_fwd, ippsWTFwd, , (const Type* psrc, Ipp32f* pdst_low, Ipp32f* pdst_high, int dst_len, IppsWTState* pstate), (psrc, pdst_low, pdst_high, dst_len, pstate), (IppsWTState, Type), MK2_IPP_WT_FWD_ASSOCIATOR_2)
    MK2_IPP_REPLACE_TEMPLATE(wt_inv, ippsWTInv, , (const Ipp32f* psrc_low, const Ipp32f* psrc_high, int src_len, Type* pdst, IppsWTState* pstate), (psrc_low, psrc_high, src_len, pdst, pstate), (IppsWTState, Type), MK2_IPP_WT_INV_ASSOCIATOR_2)


#undef MK2_IPP_WT_FWD_ASSOCIATOR
#undef MK2_IPP_WT_INV_ASSOCIATOR
#undef MK2_IPP_WT_FWD_ASSOCIATOR_2
#undef MK2_IPP_WT_INV_ASSOCIATOR_2

}}}}