//
// Created by Himatya on 2018/08/21.
//

#pragma once

#include <ipps.h>

#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp { namespace function {

#define MK2_IPP_LOGICAL_SHIFT_ASSOCIATOR(base_struct, base_func, name, desc)            \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_8u,  name, desc), (Ipp8u))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16u, name, desc), (Ipp16u)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32u, name, desc), (Ipp32u))

#define MK2_IPP_LOGICAL_SHIFT_SIGNATURE (const Type* psrc1, const Type* psrc2, Type* pdst, int len)
#define MK2_IPP_LOGICAL_SHIFT_ARGS (psrc1, psrc2, pdst, len)

    MK2_IPP_REPLACE_TEMPLATE(bit_and, ippsAnd, , MK2_IPP_LOGICAL_SHIFT_SIGNATURE, MK2_IPP_LOGICAL_SHIFT_ARGS, (Type), MK2_IPP_LOGICAL_SHIFT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(bit_or,  ippsOr,  , MK2_IPP_LOGICAL_SHIFT_SIGNATURE, MK2_IPP_LOGICAL_SHIFT_ARGS, (Type), MK2_IPP_LOGICAL_SHIFT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(bit_xor, ippsXor, , MK2_IPP_LOGICAL_SHIFT_SIGNATURE, MK2_IPP_LOGICAL_SHIFT_ARGS, (Type), MK2_IPP_LOGICAL_SHIFT_ASSOCIATOR)

#undef MK2_IPP_LOGICAL_SHIFT_SIGNATURE
#undef MK2_IPP_LOGICAL_SHIFT_ARGS

    // inplace
#define MK2_IPP_LOGICAL_SHIFT_I_SIGNATURE (const Type* psrc, Type* psrcdst, int len)
#define MK2_IPP_LOGICAL_SHIFT_I_ARGS (psrc, psrcdst, len)

    MK2_IPP_REPLACE_TEMPLATE(bit_and_inplace, ippsAnd, _I, MK2_IPP_LOGICAL_SHIFT_I_SIGNATURE, MK2_IPP_LOGICAL_SHIFT_I_ARGS, (Type), MK2_IPP_LOGICAL_SHIFT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(bit_or_inplace,  ippsOr,  _I, MK2_IPP_LOGICAL_SHIFT_I_SIGNATURE, MK2_IPP_LOGICAL_SHIFT_I_ARGS, (Type), MK2_IPP_LOGICAL_SHIFT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(bit_xor_inplace, ippsXor, _I, MK2_IPP_LOGICAL_SHIFT_I_SIGNATURE, MK2_IPP_LOGICAL_SHIFT_I_ARGS, (Type), MK2_IPP_LOGICAL_SHIFT_ASSOCIATOR)

#undef MK2_IPP_LOGICAL_SHIFT_I_SIGNATURE
#undef MK2_IPP_LOGICAL_SHIFT_I_ARGS

    // constant
#define MK2_IPP_LOGICAL_SHIFT_C_SIGNATURE (const Type* psrc, Type val, Type* pdst, int len)
#define MK2_IPP_LOGICAL_SHIFT_C_ARGS (psrc, val, pdst, len)

    MK2_IPP_REPLACE_TEMPLATE(bit_andc, ippsAndC, , MK2_IPP_LOGICAL_SHIFT_C_SIGNATURE, MK2_IPP_LOGICAL_SHIFT_C_ARGS, (Type), MK2_IPP_LOGICAL_SHIFT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(bit_orc,  ippsOrC,  , MK2_IPP_LOGICAL_SHIFT_C_SIGNATURE, MK2_IPP_LOGICAL_SHIFT_C_ARGS, (Type), MK2_IPP_LOGICAL_SHIFT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(bit_xorc, ippsXorC, , MK2_IPP_LOGICAL_SHIFT_C_SIGNATURE, MK2_IPP_LOGICAL_SHIFT_C_ARGS, (Type), MK2_IPP_LOGICAL_SHIFT_ASSOCIATOR)

#undef MK2_IPP_LOGICAL_SHIFT_C_SIGNATURE
#undef MK2_IPP_LOGICAL_SHIFT_C_ARGS

    // constant inplace
#define MK2_IPP_LOGICAL_SHIFT_C_I_SIGNATURE (Type val, Type* psrcdst, int len)
#define MK2_IPP_LOGICAL_SHIFT_C_I_ARGS (val, psrcdst, len)

    MK2_IPP_REPLACE_TEMPLATE(bit_andc_inplace, ippsAndC, _I, MK2_IPP_LOGICAL_SHIFT_C_I_SIGNATURE, MK2_IPP_LOGICAL_SHIFT_C_I_ARGS, (Type), MK2_IPP_LOGICAL_SHIFT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(bit_orc_inplace,  ippsOrC,  _I, MK2_IPP_LOGICAL_SHIFT_C_I_SIGNATURE, MK2_IPP_LOGICAL_SHIFT_C_I_ARGS, (Type), MK2_IPP_LOGICAL_SHIFT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(bit_xorc_inplace, ippsXorC, _I, MK2_IPP_LOGICAL_SHIFT_C_I_SIGNATURE, MK2_IPP_LOGICAL_SHIFT_C_I_ARGS, (Type), MK2_IPP_LOGICAL_SHIFT_ASSOCIATOR)

#undef MK2_IPP_LOGICAL_SHIFT_C_I_SIGNATURE
#undef MK2_IPP_LOGICAL_SHIFT_C_I_ARGS

    // not
    MK2_IPP_REPLACE_TEMPLATE(bit_not, ippsNot, , (const Type* psrc, Type* pdst, int len), (psrc, pdst, len), (Type), MK2_IPP_LOGICAL_SHIFT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(bit_not_inplace, ippsNot, _I, (Type* psrcdst, int len), (psrcdst, len), (Type), MK2_IPP_LOGICAL_SHIFT_ASSOCIATOR)

#undef MK2_IPP_LOGICAL_SHIFT_ASSOCIATOR

}}}}