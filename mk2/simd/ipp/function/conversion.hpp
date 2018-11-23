//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <ipps.h>

#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp {
namespace function {

#define MK2_IPP_CONVERSION_ASSOCIATOR_FLOAT_FLOAT(base_struct, base_func, name, desc)               \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f,  name, desc), (Ipp32f, Ipp32f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f,  name, desc), (Ipp64f, Ipp64f))

#define MK2_IPP_CONVERSION_ASSOCIATOR_FLOAT_COMPLEX_FLOAT(base_struct, base_func, name, desc)       \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc, name, desc), (Ipp32fc, Ipp32f))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc, name, desc), (Ipp64fc, Ipp64f))

    // power spectr real
    MK2_IPP_REPLACE_TEMPLATE(power_spectr, ippsPowerSpectr, , (const ComplexType* psrc_re, const ComplexType* psrc_im, Type* pdst, int len), (psrc_re, psrc_im, pdst, len), (ComplexType, Type), MK2_IPP_CONVERSION_ASSOCIATOR_FLOAT_FLOAT)

    // power spectr complex
    MK2_IPP_REPLACE_TEMPLATE_ADDITIVE(power_spectr, ippsPowerSpectr, , (const ComplexType* psrc, Type* pdst, int len), (psrc, pdst, len), (ComplexType, Type), MK2_IPP_CONVERSION_ASSOCIATOR_FLOAT_COMPLEX_FLOAT)

#define MK2_IPP_CONVERSION_ASSOCIATOR_FLOAT(base_struct, base_func, name, desc)             \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f,  name, desc), (Ipp32f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f,  name, desc), (Ipp64f))

#define MK2_IPP_CONVERSION_ASSOCIATOR_FLOAT_COMPLEX(base_struct, base_func, name, desc)     \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc, name, desc), (Ipp32fc))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc, name, desc), (Ipp64fc))

#define MK2_IPP_CONVERSION_FLOAT_ASSOCIATOR(base_struct, base_func, name, desc)             \
    MK2_IPP_CONVERSION_ASSOCIATOR_FLOAT(base_struct, base_func, name, desc)                 \
    MK2_IPP_CONVERSION_ASSOCIATOR_FLOAT_COMPLEX(base_struct, base_func, name, desc)

#define MK2_IPP_CONVERSION_FLIP_ASSOCIATOR(base_struct, base_func, name, desc)              \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_8u, name, desc), (Ipp8u))       \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16u, name, desc), (Ipp16u))     \
    MK2_IPP_CONVERSION_FLOAT_ASSOCIATOR(base_struct, base_func, name, desc)

    // flip
    MK2_IPP_REPLACE_TEMPLATE(flip, ippsFlip, , (const Type* psrc, Type* pdst, int len), (psrc, pdst, len), (Type), MK2_IPP_CONVERSION_FLIP_ASSOCIATOR)

    // flip inplace
    MK2_IPP_REPLACE_TEMPLATE(flip_inplace, ippsFlip, _I, (Type* psrcdst, int len), (psrcdst, len), (Type), MK2_IPP_CONVERSION_FLIP_ASSOCIATOR)

#undef MK2_IPP_CONVERSION_FLIP_ASSOCIATOR

#define MK2_IPP_CONVERSION_THRESHOLD_ASSOCIATOR(base_struct, base_func, name, desc)         \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s, name, desc), (Ipp16s))     \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16sc, name, desc), (Ipp16sc))   \
    MK2_IPP_CONVERSION_FLOAT_ASSOCIATOR(base_struct, base_func, name, desc)

    // threshold
    MK2_IPP_REPLACE_TEMPLATE(threshold, ippsThreshold, , (const Type* psrc, Type* pdst, int len, Ipp16s level, IppCmpOp rel_op), (psrc, pdst, len, level, rel_op), (Type), MK2_IPP_CONVERSION_THRESHOLD_ASSOCIATOR)

    // flip inplace
    MK2_IPP_REPLACE_TEMPLATE(threshold_inplace, ippsThreshold, _I, (Type* psrcdst, int len, Ipp16s level, IppCmpOp rel_op), (psrcdst, len, level, rel_op), (Type), MK2_IPP_CONVERSION_THRESHOLD_ASSOCIATOR)

#undef MK2_IPP_CONVERSION_THRESHOLD_ASSOCIATOR

#define MK2_IPP_CONVERSION_THRESHOLD_LTGT_ASSOCIATOR(base_struct, base_func, name, desc)            \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s,  name, desc), (Ipp16s, Ipp16s))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32s,  name, desc), (Ipp32s, Ipp32s))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16sc, name, desc), (Ipp16sc, Ipp16s))   \
    MK2_IPP_CONVERSION_ASSOCIATOR_FLOAT_FLOAT(base_struct, base_func, name, desc)                   \
    MK2_IPP_CONVERSION_ASSOCIATOR_FLOAT_COMPLEX_FLOAT(base_struct, base_func, name, desc)

    // threshold LTGT
    MK2_IPP_REPLACE_TEMPLATE(threshold_lt, ippsThreshold_LT, , (const Type1* psrc, Type1* pdst, int len, Type2 level), (psrc, pdst, len, level), (Type1, Type2), MK2_IPP_CONVERSION_THRESHOLD_LTGT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(threshold_gt, ippsThreshold_GT, , (const Type1* psrc, Type1* pdst, int len, Type2 level), (psrc, pdst, len, level), (Type1, Type2), MK2_IPP_CONVERSION_THRESHOLD_LTGT_ASSOCIATOR)

    // threshold LTGT inplace
    MK2_IPP_REPLACE_TEMPLATE(threshold_lt_inplace, ippsThreshold_LT, _I, (Type1* psrcdst, int len, Type2 level), (psrcdst, len, level), (Type1, Type2), MK2_IPP_CONVERSION_THRESHOLD_LTGT_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(threshold_gt_inplace, ippsThreshold_GT, _I, (Type1* psrcdst, int len, Type2 level), (psrcdst, len, level), (Type1, Type2), MK2_IPP_CONVERSION_THRESHOLD_LTGT_ASSOCIATOR)

#undef MK2_IPP_CONVERSION_THRESHOLD_LTGT_ASSOCIATOR

#define MK2_IPP_CONVERSION_CONVERT_ASSOCIATOR(base_struct, base_func, name, desc)                   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_8s16s,  name, desc), (Ipp8s,  Ipp16s))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_8s32f,  name, desc), (Ipp8s,  Ipp32f))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_8s32f,  name, desc), (Ipp8u,  Ipp32f))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_8s8u,   name, desc), (Ipp8s,  Ipp8u ))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s32s, name, desc), (Ipp16s, Ipp32s))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s32f, name, desc), (Ipp16s, Ipp32f))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16u32f, name, desc), (Ipp16u, Ipp32f))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32s16s, name, desc), (Ipp32s, Ipp16s))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32s32f, name, desc), (Ipp32s, Ipp32f))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32s64f, name, desc), (Ipp32s, Ipp64f))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f64f, name, desc), (Ipp32f, Ipp64f))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64s64f, name, desc), (Ipp64s, Ipp64f))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f32f, name, desc), (Ipp64f, Ipp32f))

    MK2_IPP_REPLACE_TEMPLATE(convert, ippsConvert, , (const Type1* psrc, Type2* pdst, int len), (psrc, pdst, len), (Type1, Type2), MK2_IPP_CONVERSION_CONVERT_ASSOCIATOR)

#undef MK2_IPP_CONVERSION_CONVERT_ASSOCIATOR

#define MK2_IPP_CONVERSION_CONVERT_SFS_ASSOCIATOR(base_struct, base_func, name, desc)               \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s32f, name, desc), (Ipp16s, Ipp32f))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s64f, name, desc), (Ipp16s, Ipp64f))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32s16s, name, desc), (Ipp32s, Ipp16s))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32s32f, name, desc), (Ipp32s, Ipp32f))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32s64f, name, desc), (Ipp32s, Ipp64f))

    MK2_IPP_REPLACE_TEMPLATE(convert_sfs, ippsConvert, _Sfs, (const Type1* psrc, Type2* pdst, int len, int scale_factor = 0), (psrc, pdst, len, scale_factor), (Type1, Type2), MK2_IPP_CONVERSION_CONVERT_SFS_ASSOCIATOR)

#undef MK2_IPP_CONVERSION_CONVERT_SFS_ASSOCIATOR

#define MK2_IPP_CONVERSION_CONVERT_F2I_ASSOCIATOR(base_struct, base_func, name, desc)               \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_8u8s,   name, desc), (Ipp8u,  Ipp8s))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s8s,  name, desc), (Ipp16s, Ipp8s))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f8s,  name, desc), (Ipp32f, Ipp8s))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f8u,  name, desc), (Ipp32f, Ipp8u))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f16s, name, desc), (Ipp32f, Ipp16s))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f16u, name, desc), (Ipp32f, Ipp16u))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f32s, name, desc), (Ipp32f, Ipp32s))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f8s,  name, desc), (Ipp64f, Ipp8s))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f8u,  name, desc), (Ipp64f, Ipp8u))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f16s, name, desc), (Ipp64f, Ipp16s))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f16u, name, desc), (Ipp64f, Ipp16u))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f32s, name, desc), (Ipp64f, Ipp32s))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f64s, name, desc), (Ipp64f, Ipp64s))

    MK2_IPP_REPLACE_TEMPLATE(convert_f2i, ippsConvert, _Sfs, (const Type1* psrc, Type2* pdst, int len, IppRoundMode rnd_mode = ippRndZero, int scale_factor = 0), (psrc, pdst, len, rnd_mode, scale_factor), (Type1, Type2), MK2_IPP_CONVERSION_CONVERT_F2I_ASSOCIATOR)

#undef MK2_IPP_CONVERSION_CONVERT_F2I_ASSOCIATOR

#undef MK2_IPP_CONVERSION_ASSOCIATOR_FLOAT_FLOAT
#undef MK2_IPP_CONVERSION_ASSOCIATOR_FLOAT_COMPLEX_FLOAT

#undef MK2_IPP_CONVERSION_ASSOCIATOR_FLOAT
#undef MK2_IPP_CONVERSION_ASSOCIATOR_FLOAT_COMPLEX
#undef MK2_IPP_CONVERSION_FLOAT_ASSOCIATOR

}}}}