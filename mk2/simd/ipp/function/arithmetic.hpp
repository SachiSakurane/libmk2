//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <ipps.h>

#include <mk2/preprocessor/template_wrapper.hpp>
#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp {
namespace function {

#define MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING_DIV(base_struct, base_func, name, desc)       \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_8u,   name, desc), (Ipp8u))     \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s,  name, desc), (Ipp16s))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16u,  name, desc), (Ipp16u))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32s,  name, desc), (Ipp32s))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16sc, name, desc), (Ipp16sc))

#define MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING(base_struct, base_func, name, desc)           \
    MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING_DIV(base_struct, base_func, name, desc)           \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32sc,  name, desc), (Ipp32sc))

#define MK2_IPP_ARITHMETIC_ASSOCIATOR_FLOAT(base_struct, base_func, name, desc)             \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f,  name, desc), (Ipp32f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f,  name, desc), (Ipp64f))

#define MK2_IPP_ARITHMETIC_ASSOCIATOR_FLOAT_COMPLEX(base_struct, base_func, name, desc)     \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc, name, desc), (Ipp32fc))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc, name, desc), (Ipp64fc))

#define MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR(base_struct, base_func, name, desc)             \
    MK2_IPP_ARITHMETIC_ASSOCIATOR_FLOAT(base_struct, base_func, name, desc)                 \
    MK2_IPP_ARITHMETIC_ASSOCIATOR_FLOAT_COMPLEX(base_struct, base_func, name, desc)

#define MK2_IPP_ARITHMETIC_ASSOCIATOR(base_struct, base_func, name, desc)                   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s,  name, desc), (Ipp16s))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16u,  name, desc), (Ipp16u))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32u,  name, desc), (Ipp32u))    \
    MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR(base_struct, base_func, name, desc)

    // common
#define MK2_IPP_ARITHMETIC_SIGNATURE    (const Type* psrc1, const Type* psrc2, Type* pdst, int len)
#define MK2_IPP_ARITHMETIC_ARGS         (psrc1, psrc2, pdst, len)

    MK2_IPP_REPLACE_TEMPLATE(add, ippsAdd, , MK2_IPP_ARITHMETIC_SIGNATURE, MK2_IPP_ARITHMETIC_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(sub, ippsSub, , MK2_IPP_ARITHMETIC_SIGNATURE, MK2_IPP_ARITHMETIC_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(mul, ippsMul, , MK2_IPP_ARITHMETIC_SIGNATURE, MK2_IPP_ARITHMETIC_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(div, ippsDiv, , MK2_IPP_ARITHMETIC_SIGNATURE, MK2_IPP_ARITHMETIC_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR)

#undef MK2_IPP_ARITHMETIC_SIGNATURE
#undef MK2_IPP_ARITHMETIC_ARGS

    // inplace
#define MK2_IPP_ARITHMETIC_I_SIGNATURE    (const Type* psrc, Type* psrc_dst, int len)
#define MK2_IPP_ARITHMETIC_I_ARGS         (psrc, psrc_dst, len)

    MK2_IPP_REPLACE_TEMPLATE(add_inplace, ippsAdd, _I, MK2_IPP_ARITHMETIC_I_SIGNATURE, MK2_IPP_ARITHMETIC_I_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(sub_inplace, ippsSub, _I, MK2_IPP_ARITHMETIC_I_SIGNATURE, MK2_IPP_ARITHMETIC_I_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(mul_inplace, ippsMul, _I, MK2_IPP_ARITHMETIC_I_SIGNATURE, MK2_IPP_ARITHMETIC_I_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(div_inplace, ippsDiv, _I, MK2_IPP_ARITHMETIC_I_SIGNATURE, MK2_IPP_ARITHMETIC_I_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR)

#undef MK2_IPP_ARITHMETIC_I_SIGNATURE
#undef MK2_IPP_ARITHMETIC_I_ARGS

    // constant
#define MK2_IPP_ARITHMETIC_C_SIGNATURE    (const Type* psrc, Type val, Type* pdst, int len)
#define MK2_IPP_ARITHMETIC_C_ARGS         (psrc, val, pdst, len)

    MK2_IPP_REPLACE_TEMPLATE(addc, ippsAddC, , MK2_IPP_ARITHMETIC_C_SIGNATURE, MK2_IPP_ARITHMETIC_C_ARGS, (Type), MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(subc, ippsSubC, , MK2_IPP_ARITHMETIC_C_SIGNATURE, MK2_IPP_ARITHMETIC_C_ARGS, (Type), MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(mulc, ippsMulC, , MK2_IPP_ARITHMETIC_C_SIGNATURE, MK2_IPP_ARITHMETIC_C_ARGS, (Type), MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(divc, ippsDivC, , MK2_IPP_ARITHMETIC_C_SIGNATURE, MK2_IPP_ARITHMETIC_C_ARGS, (Type), MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(subc_rev, ippsSubCRev, , MK2_IPP_ARITHMETIC_C_SIGNATURE, MK2_IPP_ARITHMETIC_C_ARGS, (Type), MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(divc_rev, ippsDivCRev, , MK2_IPP_ARITHMETIC_C_SIGNATURE, MK2_IPP_ARITHMETIC_C_ARGS, (Type), MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR)

#undef MK2_IPP_ARITHMETIC_C_SIGNATURE
#undef MK2_IPP_ARITHMETIC_C_ARGS

    // constant inplace
#define MK2_IPP_ARITHMETIC_C_I_SIGNATURE    (Type val, Type* psrc_dst, int len)
#define MK2_IPP_ARITHMETIC_C_I_ARGS         (val, psrc_dst, len)

    MK2_IPP_REPLACE_TEMPLATE(addc_inplace, ippsAddC, _I, MK2_IPP_ARITHMETIC_C_I_SIGNATURE, MK2_IPP_ARITHMETIC_C_I_ARGS, (Type), MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(subc_inplace, ippsSubC, _I, MK2_IPP_ARITHMETIC_C_I_SIGNATURE, MK2_IPP_ARITHMETIC_C_I_ARGS, (Type), MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(mulc_inplace, ippsMulC, _I, MK2_IPP_ARITHMETIC_C_I_SIGNATURE, MK2_IPP_ARITHMETIC_C_I_ARGS, (Type), MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(divc_inplace, ippsDivC, _I, MK2_IPP_ARITHMETIC_C_I_SIGNATURE, MK2_IPP_ARITHMETIC_C_I_ARGS, (Type), MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(subc_rev_inplace, ippsSubCRev, _I, MK2_IPP_ARITHMETIC_C_I_SIGNATURE, MK2_IPP_ARITHMETIC_C_I_ARGS, (Type), MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(divc_rev_inplace, ippsDivCRev, _I, MK2_IPP_ARITHMETIC_C_I_SIGNATURE, MK2_IPP_ARITHMETIC_C_I_ARGS, (Type), MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR)

#undef MK2_IPP_ARITHMETIC_C_I_SIGNATURE
#undef MK2_IPP_ARITHMETIC_C_I_ARGS

    // add product
    MK2_IPP_REPLACE_TEMPLATE(addprod, ippsAddProduct, , (const Type* psrc1, const Type* psrc2, Type* psrcdst, int len), (psrc1, psrc2, psrcdst, len), (Type), MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR)

    // add product constant
    MK2_IPP_REPLACE_TEMPLATE(addprodc, ippsAddProductC, , (const Type* psrc, Type val, Type* psrc_dst, int len), (psrc, val, psrc_dst, len), (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_FLOAT)

    // sqrt
    MK2_IPP_REPLACE_TEMPLATE(sqrt, ippsSqrt, , (const Type* psrc, Type* pdst, int len), (psrc, pdst, len), (Type), MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR)

    // sqrt inplace
    MK2_IPP_REPLACE_TEMPLATE(sqrt_inplace, ippsSqrt, _I, (Type* psrc_dst, int len), (psrc_dst, len), (Type), MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR)

    // normalize
    MK2_IPP_REPLACE_TEMPLATE(normalize, ippsNormalize, , (const Type* psrc, Type* pdst, int len, Type vsub, Type vdiv), (psrc, pdst, len, vsub, vdiv), (Type), MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR)

    // normalize inplace
    MK2_IPP_REPLACE_TEMPLATE(normalize_inplace, ippsNormalize, _I, (Type* psrc_dst, int len, Type vsub, Type vdiv), (psrc_dst, len, vsub, vdiv), (Type), MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR)

#define MK2_IPP_ARITHMETIC_SFS_SIGNATURE    (const Type* psrc1, const Type* psrc2, Type* pdst, int len, int scale_factor = 0)
#define MK2_IPP_ARITHMETIC_SFS_ARGS         (psrc1, psrc2, pdst, len, scale_factor)

    MK2_IPP_REPLACE_TEMPLATE(add_sfs, ippsAdd, _Sfs, MK2_IPP_ARITHMETIC_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING)
    MK2_IPP_REPLACE_TEMPLATE(sub_sfs, ippsSub, _Sfs, MK2_IPP_ARITHMETIC_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING)
    MK2_IPP_REPLACE_TEMPLATE(mul_sfs, ippsMul, _Sfs, MK2_IPP_ARITHMETIC_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING)
    MK2_IPP_REPLACE_TEMPLATE(div_sfs, ippsDiv, _Sfs, MK2_IPP_ARITHMETIC_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING_DIV)

#undef MK2_IPP_ARITHMETIC_SFS_SIGNATURE
#undef MK2_IPP_ARITHMETIC_SFS_ARGS

#define MK2_IPP_ARITHMETIC_C_SFS_SIGNATURE    (const Type* psrc, Type val, Type* pdst, int len, int scale_factor = 0)
#define MK2_IPP_ARITHMETIC_C_SFS_ARGS         (psrc, val, pdst, len, scale_factor)

    MK2_IPP_REPLACE_TEMPLATE(addc_sfs, ippsAddC, _Sfs, MK2_IPP_ARITHMETIC_C_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_C_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING)
    MK2_IPP_REPLACE_TEMPLATE(subc_sfs, ippsSubC, _Sfs, MK2_IPP_ARITHMETIC_C_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_C_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING)
    MK2_IPP_REPLACE_TEMPLATE(mulc_sfs, ippsMulC, _Sfs, MK2_IPP_ARITHMETIC_C_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_C_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING)
    MK2_IPP_REPLACE_TEMPLATE(divc_sfs, ippsDivC, _Sfs, MK2_IPP_ARITHMETIC_C_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_C_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING_DIV)
    MK2_IPP_REPLACE_TEMPLATE(subc_rev_sfs, ippsSubCRev, _Sfs, MK2_IPP_ARITHMETIC_C_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_C_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING)
    MK2_IPP_REPLACE_TEMPLATE(divc_rev_sfs, ippsDivCRev, _Sfs, MK2_IPP_ARITHMETIC_C_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_C_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING_DIV)

#undef MK2_IPP_ARITHMETIC_C_SFS_SIGNATURE
#undef MK2_IPP_ARITHMETIC_C_SFS_ARGS

#define MK2_IPP_ARITHMETIC_I_SFS_SIGNATURE    (const Type* psrc, Type* psrcdst, int len, int scale_factor = 0)
#define MK2_IPP_ARITHMETIC_I_SFS_ARGS         (psrc, psrcdst, len, scale_factor)

    MK2_IPP_REPLACE_TEMPLATE(add_inplace_sfs, ippsAdd, _ISfs, MK2_IPP_ARITHMETIC_I_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_I_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING)
    MK2_IPP_REPLACE_TEMPLATE(sub_inplace_sfs, ippsSub, _ISfs, MK2_IPP_ARITHMETIC_I_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_I_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING)
    MK2_IPP_REPLACE_TEMPLATE(mul_inplace_sfs, ippsMul, _ISfs, MK2_IPP_ARITHMETIC_I_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_I_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING)
    MK2_IPP_REPLACE_TEMPLATE(div_inplace_sfs, ippsDiv, _ISfs, MK2_IPP_ARITHMETIC_I_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_I_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING_DIV)

#undef MK2_IPP_ARITHMETIC_I_SFS_SIGNATURE
#undef MK2_IPP_ARITHMETIC_I_SFS_ARGS

#define MK2_IPP_ARITHMETIC_C_I_SFS_SIGNATURE    (Type val, Type* psrcdst, int len, int scale_factor = 0)
#define MK2_IPP_ARITHMETIC_C_I_SFS_ARGS         (val, psrcdst, len, scale_factor)

    MK2_IPP_REPLACE_TEMPLATE(addc_inplace_sfs, ippsAddC, _ISfs, MK2_IPP_ARITHMETIC_C_I_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_C_I_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING)
    MK2_IPP_REPLACE_TEMPLATE(subc_inplace_sfs, ippsSubC, _ISfs, MK2_IPP_ARITHMETIC_C_I_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_C_I_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING)
    MK2_IPP_REPLACE_TEMPLATE(mulc_inplace_sfs, ippsMulC, _ISfs, MK2_IPP_ARITHMETIC_C_I_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_C_I_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING)
    MK2_IPP_REPLACE_TEMPLATE(divc_inplace_sfs, ippsDivC, _ISfs, MK2_IPP_ARITHMETIC_C_I_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_C_I_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING_DIV)
    MK2_IPP_REPLACE_TEMPLATE(subc_inplace_rev_sfs, ippsSubCRev, _ISfs, MK2_IPP_ARITHMETIC_C_I_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_C_I_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING)
    MK2_IPP_REPLACE_TEMPLATE(divc_inplace_rev_sfs, ippsDivCRev, _ISfs, MK2_IPP_ARITHMETIC_C_I_SFS_SIGNATURE, MK2_IPP_ARITHMETIC_C_I_SFS_ARGS, (Type), MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING_DIV)

#undef MK2_IPP_ARITHMETIC_C_I_SFS_SIGNATURE
#undef MK2_IPP_ARITHMETIC_C_I_SFS_ARGS

#undef MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING
#undef MK2_IPP_ARITHMETIC_ASSOCIATOR_SCALING_DIV
#undef MK2_IPP_ARITHMETIC_ASSOCIATOR_FLOAT
#undef MK2_IPP_ARITHMETIC_ASSOCIATOR_FLOAT_COMPLEX
#undef MK2_IPP_ARITHMETIC_FLOAT_ASSOCIATOR
#undef MK2_IPP_ARITHMETIC_ASSOCIATOR
/*
    // c scaling
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_8u##descriptor, Ipp8u)      \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16u##descriptor, Ipp16u)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16s##descriptor, Ipp16s)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32s##descriptor, Ipp32s)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16sc##descriptor, Ipp16sc)  \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32sc##descriptor, Ipp32sc)

    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type val, Type* pdst, int len, int scale_factor = 0

    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, val, pdst, len, scale_factor

    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_addc_sfs, ippsAddC, _Sfs, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_subc_sfs, ippsSubC, _Sfs, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_mulc_sfs, ippsMulC, _Sfs, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_subc_rev_sfs, ippsSubCRev, _Sfs, Type)

    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS

    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    Type val, Type* psrc_dst, int len, int scale_factor = 0

    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    val, psrc_dst, len, scale_factor

    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_addc_inplace_sfs, ippsAddC, _ISfs, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_subc_inplace_sfs, ippsSubC, _ISfs, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_mulc_inplace_sfs, ippsMulC, _ISfs, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_subc_rev_inplace_sfs, ippsSubCRev, _ISfs, Type)

    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS

    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR
    */
}}}}