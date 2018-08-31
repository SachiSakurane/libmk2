//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <ipps.h>

#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp { namespace function {
    
    // real
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f##descriptor, Ipp32f, Ipp32f)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f##descriptor, Ipp64f, Ipp64f)
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const ComplexType* psrc_re, const ComplexType* psrc_im, Type* pdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc_re, psrc_im, pdst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_power_spectr, ippsPowerSpectr, , ComplexType, Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR
    
    // complex
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc##descriptor, Ipp32fc, Ipp32f)  \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc##descriptor, Ipp64fc, Ipp64f)
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const ComplexType* psrc, Type* pdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ADDITIVE(ipps_power_spectr, ippsPowerSpectr, , ComplexType, Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR
    
    // flip
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_8u##descriptor, Ipp8u)      \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16u##descriptor, Ipp16u)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f##descriptor, Ipp32f)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f##descriptor, Ipp64f)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc##descriptor, Ipp32fc)  \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc##descriptor, Ipp64fc)
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type* pdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_flip, ippsFlip, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    Type* psrcdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrcdst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_flip_inplace, ippsFlip, _I, Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR
                
    // threshold
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16s##descriptor, Ipp16s)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16sc##descriptor, Ipp16sc)  \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f##descriptor, Ipp32f)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f##descriptor, Ipp64f)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc##descriptor, Ipp32fc)  \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc##descriptor, Ipp64fc)
                
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type* pdst, int len, Ipp16s level, IppCmpOp rel_op
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len, level, rel_op
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_threshold, ippsThreshold, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    Type* psrcdst, int len, Ipp16s level, IppCmpOp rel_op
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrcdst, len, level, rel_op
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_threshold_inplace, ippsThreshold, _I, Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR

    // threshold LTGT
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16s##descriptor, Ipp16s, Ipp16s)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32s##descriptor, Ipp32s, Ipp32s)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f##descriptor, Ipp32f, Ipp32f)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f##descriptor, Ipp64f, Ipp64f)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16sc##descriptor, Ipp16sc, Ipp16s)  \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc##descriptor, Ipp32fc, Ipp32f)  \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc##descriptor, Ipp64fc, Ipp64f)

    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type1* psrc, Type1* pdst, int len, Type2 level

    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len, level

    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_threshold_lt, ippsThreshold_LT, , Type1, Type2)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_threshold_gt, ippsThreshold_GT, , Type1, Type2)

    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS

    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    Type1* psrcdst, int len, Type2 level

    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrcdst, len, level

    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_threshold_lt_inplace, ippsThreshold_LT, _I, Type1, Type2)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_threshold_gt_inplace, ippsThreshold_GT, _I, Type1, Type2)

    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS

    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR


    // convert
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_8s16s##descriptor, Ipp8s, Ipp16s)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_8s32f##descriptor, Ipp8s, Ipp32f)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_8s32f##descriptor, Ipp8u, Ipp32f)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_8s8u##descriptor, Ipp8s, Ipp8u)     \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16s32s##descriptor, Ipp16s, Ipp32s) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16s32f##descriptor, Ipp16s, Ipp32f) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16u32f##descriptor, Ipp16u, Ipp32f) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32s16s##descriptor, Ipp32s, Ipp16s) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32s32f##descriptor, Ipp32s, Ipp32f) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32s64f##descriptor, Ipp32s, Ipp64f) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f64f##descriptor, Ipp32f, Ipp64f) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64s64f##descriptor, Ipp64s, Ipp64f) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f32f##descriptor, Ipp64f, Ipp32f)
    //IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_24u32u##descriptor, Ipp24u, Ipp32u) \
    //IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_24u32f##descriptor, Ipp24u, Ipp32f)
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type1* psrc, Type2* pdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_convert, ippsConvert, , Type1, Type2)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)            \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_8u8s##descriptor, Ipp8u, Ipp8s)     \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16s8s##descriptor, Ipp16s, Ipp8s)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16s32f##descriptor, Ipp16s, Ipp32f) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_16s64f##descriptor, Ipp16s, Ipp64f) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32s16s##descriptor, Ipp32s, Ipp16s) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32s32f##descriptor, Ipp32s, Ipp32f) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32s64f##descriptor, Ipp32s, Ipp64f)
    //IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32u24u##descriptor, Ipp32u, Ipp24u) \
    //IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f24u##descriptor, Ipp32f, Ipp24u) \
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type1* psrc, Type2* pdst, int len, int scale_factor = 0
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len, scale_factor
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_convert_sfs, ippsConvert, _Sfs, Type1, Type2)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)            \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f8s##descriptor, Ipp32f, Ipp8s)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f8u##descriptor, Ipp32f, Ipp8u)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f16s##descriptor, Ipp32f, Ipp16s) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f16u##descriptor, Ipp32f, Ipp16u) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f32s##descriptor, Ipp32f, Ipp32s) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f8s##descriptor, Ipp64f, Ipp8s)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f8u##descriptor, Ipp64f, Ipp8u)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f16s##descriptor, Ipp64f, Ipp16s) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f16u##descriptor, Ipp64f, Ipp16u) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f32s##descriptor, Ipp64f, Ipp32s) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f64s##descriptor, Ipp64f, Ipp64s)
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type1* psrc, Type2* pdst, int len, IppRoundMode rnd_mode = ippRndZero, int scale_factor = 0
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len, rnd_mode, scale_factor
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_convert_f2i, ippsConvert, _Sfs, Type1, Type2)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR
}}}}