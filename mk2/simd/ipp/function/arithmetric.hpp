//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <ipps.h>

#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp { namespace function {
    
    // common
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16s##descriptor, Ipp16s)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f##descriptor, Ipp32f)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f##descriptor, Ipp64f)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc##descriptor, Ipp32fc)  \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc##descriptor, Ipp64fc)  \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16u##descriptor, Ipp16u)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32u##descriptor, Ipp32u)
    
    // not inplace
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc1, const Type* psrc2, Type* pdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc1, psrc2, pdst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_add, ippsAdd, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_sub, ippsSub, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_mul, ippsMul, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_div, ippsDiv, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    
    // inplace
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type* psrc_dst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, psrc_dst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_add_inplace, ippsAdd, _I, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_sub_inplace, ippsSub, _I, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_mul_inplace, ippsMul, _I, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_div_inplace, ippsDiv, _I, Type)

    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
                
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR


    // c
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f##descriptor, Ipp32f)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f##descriptor, Ipp64f)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc##descriptor, Ipp32fc)  \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc##descriptor, Ipp64fc)
                
    // not inplace
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type val, Type* pdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, val, pdst, len
                
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_addc, ippsAddC, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_subc, ippsSubC, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_mulc, ippsMulC, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_divc, ippsDivC, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_subc_rev, ippsSubCRev, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_divc_rev, ippsDivCRev, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    // c inplace
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    Type val, Type* psrc_dst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    val, psrc_dst, len

    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_addc_inplace, ippsAddC, _I, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_subc_inplace, ippsSubC, _I, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_mulc_inplace, ippsMulC, _I, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_divc_inplace, ippsDivC, _I, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_subc_rev_inplace, ippsSubCRev, _I, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_divc_rev_inplace, ippsDivCRev, _I, Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    // add product
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc1, const Type* psrc2, Type* psrcdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc1, psrc2, psrcdst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_add_product, ippsAddProduct, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    // arithmetic not inplace
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type* pdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len
                
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_sqrt, ippsSqrt, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    // arithmetic inplace
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    Type* psrc_dst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc_dst, len
                
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_sqrt_inplace, ippsSqrt, _I, Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
                
    // normalize not inplace
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type* pdst, int len, Type vsub, Type vdiv
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len, vsub, vdiv
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_normalize, ippsNormalize, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    // normalize inplace
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    Type* psrc_dst, int len, Type vsub, Type vdiv
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc_dst, len, vsub, vdiv
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_normalize_inplace, ippsNormalize, _I, Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR
    
    
    // product c
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f##descriptor, Ipp32f)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f##descriptor, Ipp64f)
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type val, Type* psrc_dst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, val, psrc_dst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_add_product_c, ippsAddProductC, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR


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
    
}}}}