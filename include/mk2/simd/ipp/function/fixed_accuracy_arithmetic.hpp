//
// Created by Himatya on 2018/08/17.
//

#pragma once

#include <mk2/simd/ipp/include.hpp>
#include <mk2/simd/ipp/function/float_precision.hpp>
#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp {
namespace function {
#define MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT(base_struct, base_func, name, desc)              \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f_A11, name, desc), (Ipp32f, precision_low_t))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f_A21, name, desc), (Ipp32f, precision_mid_t))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f_A24, name, desc), (Ipp32f, precision_high_t)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f_A26, name, desc), (Ipp64f, precision_low_t))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f_A50, name, desc), (Ipp64f, precision_mid_t))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f_A53, name, desc), (Ipp64f, precision_high_t))

#define MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT_COMPLEX(base_struct, base_func, name, desc)          \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc_A11, name, desc), (Ipp32fc, precision_low_t))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc_A21, name, desc), (Ipp32fc, precision_mid_t))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc_A24, name, desc), (Ipp32fc, precision_high_t))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc_A26, name, desc), (Ipp64fc, precision_low_t))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc_A50, name, desc), (Ipp64fc, precision_mid_t))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc_A53, name, desc), (Ipp64fc, precision_high_t))

#define MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT_FLOAT_COMPLEX(base_struct, base_func, name, desc)            \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc_A11, name, desc), (Ipp32f, Ipp32fc, precision_low_t))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc_A21, name, desc), (Ipp32f, Ipp32fc, precision_mid_t))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc_A24, name, desc), (Ipp32f, Ipp32fc, precision_high_t))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc_A26, name, desc), (Ipp64f, Ipp64fc, precision_low_t))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc_A50, name, desc), (Ipp64f, Ipp64fc, precision_mid_t))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc_A53, name, desc), (Ipp64f, Ipp64fc, precision_high_t))

#define MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR(base_struct, base_func, name, desc)    \
    MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT(base_struct, base_func, name, desc)  \
    MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT_COMPLEX(base_struct, base_func, name, desc)

#define MK2_IPP_FAA_UNARY_SIGNATURE (const Type* psrc, Type* pdst, Ipp32s len, PrecisionType)
#define MK2_IPP_FAA_UNARY_ARGS (psrc, pdst, len)
#define MK2_IPP_FAA_BINARY_SIGNATURE (const Type* psrc1, const Type* psrc2, Type* pdst, Ipp32s len, PrecisionType)
#define MK2_IPP_FAA_BINARY_ARGS (psrc1, psrc2, pdst, len)

    // arithmetic
    // inv
    MK2_IPP_REPLACE_TEMPLATE(inv, ippsInv, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT)
    
    // hypot
    MK2_IPP_REPLACE_TEMPLATE(hypot, ippsHypot, , MK2_IPP_FAA_BINARY_SIGNATURE, MK2_IPP_FAA_BINARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)

    // root
    // sqrt
    MK2_IPP_REPLACE_TEMPLATE(faa_sqrt, ippsSqrt, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)

    // inv sqrt
    MK2_IPP_REPLACE_TEMPLATE(inv_sqrt, ippsInvSqrt, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT)
    
    // cbrt
    MK2_IPP_REPLACE_TEMPLATE(cbrt, ippsCbrt, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT)
    
    // inv cbrt
    MK2_IPP_REPLACE_TEMPLATE(inv_cbrt, ippsInvCbrt, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT)

    // pow
    // pow2o3
    MK2_IPP_REPLACE_TEMPLATE(pow2o3, ippsPow2o3, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT)
    
    // pow3o2
    MK2_IPP_REPLACE_TEMPLATE(pow3o2, ippsPow3o2, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT)
    
    // pow
    MK2_IPP_REPLACE_TEMPLATE(pow, ippsPow, , MK2_IPP_FAA_BINARY_SIGNATURE, MK2_IPP_FAA_BINARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)

    // powx
    MK2_IPP_REPLACE_TEMPLATE(powx, ippsPowx, , (const Type* psrc, const Type v, Type* pdst, Ipp32s len, PrecisionType), (psrc, v, pdst, len), (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)

    // exponential
    // exp
    MK2_IPP_REPLACE_TEMPLATE(exp, ippsExp, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)
    
    // expm1
    MK2_IPP_REPLACE_TEMPLATE(expm1, ippsExpm1, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT)
    
    // logarithmic
    // ln
    MK2_IPP_REPLACE_TEMPLATE(ln, ippsLn, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)
    
    // log10
    MK2_IPP_REPLACE_TEMPLATE(log10, ippsLog10, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)
    
    // log1p
    MK2_IPP_REPLACE_TEMPLATE(log1p, ippsLog1p, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT)
    
    // trigonometric
    // cos
    MK2_IPP_REPLACE_TEMPLATE(cos, ippsCos, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)
    
    // sin
    MK2_IPP_REPLACE_TEMPLATE(sin, ippsSin, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)

    // tan
    MK2_IPP_REPLACE_TEMPLATE(tan, ippsTan, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)
    
    // acos
    MK2_IPP_REPLACE_TEMPLATE(acos, ippsAcos, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)
    
    // asin
    MK2_IPP_REPLACE_TEMPLATE(asin, ippsAsin, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)

    // atan
    MK2_IPP_REPLACE_TEMPLATE(atan, ippsAtan, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)

    // atan2
    MK2_IPP_REPLACE_TEMPLATE(atan2, ippsAtan2, , MK2_IPP_FAA_BINARY_SIGNATURE, MK2_IPP_FAA_BINARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT)

    // sincos
    MK2_IPP_REPLACE_TEMPLATE(sin_cos, ippsSinCos, , MK2_IPP_FAA_BINARY_SIGNATURE, MK2_IPP_FAA_BINARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT)

    // CIS
    MK2_IPP_REPLACE_TEMPLATE(cis, ippsCIS, , (const Type* psrc, ComplexType* pdst, Ipp32s len, PrecisionType), (psrc, pdst, len), (Type, ComplexType, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT_FLOAT_COMPLEX)

    // hyparbolic
    // cos
    MK2_IPP_REPLACE_TEMPLATE(cosh, ippsCosh, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)
    
    // sin
    MK2_IPP_REPLACE_TEMPLATE(sinh, ippsSinh, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)

    // tan
    MK2_IPP_REPLACE_TEMPLATE(tanh, ippsTanh, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)
    
    // acos
    MK2_IPP_REPLACE_TEMPLATE(acosh, ippsAcosh, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)
    
    // asin
    MK2_IPP_REPLACE_TEMPLATE(asinh, ippsAsinh, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)

    // atan
    MK2_IPP_REPLACE_TEMPLATE(atanh, ippsAtanh, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)

    // special
    // error function
    MK2_IPP_REPLACE_TEMPLATE(erf, ippsErf, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT)

    // erfc
    MK2_IPP_REPLACE_TEMPLATE(erfc, ippsErfc, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT)

    // inv erf
    MK2_IPP_REPLACE_TEMPLATE(erf_inv, ippsErfInv, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT)

    // inv erfc
    MK2_IPP_REPLACE_TEMPLATE(erfc_inv, ippsErfcInv, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT)

    // cumulative normal distribution function
    MK2_IPP_REPLACE_TEMPLATE(cdf_norm, ippsCdfNorm, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT)

    // inv cdf norm
    MK2_IPP_REPLACE_TEMPLATE(cdf_norm_inv, ippsCdfNormInv, , MK2_IPP_FAA_UNARY_SIGNATURE, MK2_IPP_FAA_UNARY_ARGS, (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT)

#undef MK2_IPP_FAA_UNARY_SIGNATURE
#undef MK2_IPP_FAA_UNARY_ARGS
#undef MK2_IPP_FAA_BINARY_SIGNATURE
#undef MK2_IPP_FAA_BINARY_ARGS

#define MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_2(base_struct, base_func, name, desc)                              \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f_A24,  name, desc), (Ipp32f, Ipp32f, precision_high_t))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f_A53,  name, desc), (Ipp64f, Ipp32f, precision_high_t))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc_A11, name, desc), (Ipp32fc, Ipp32f, precision_low_t))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc_A21, name, desc), (Ipp32fc, Ipp32f, precision_mid_t))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc_A24, name, desc), (Ipp32fc, Ipp32f, precision_high_t))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc_A26, name, desc), (Ipp64fc, Ipp64f, precision_low_t))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc_A50, name, desc), (Ipp64fc, Ipp64f, precision_mid_t))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc_A53, name, desc), (Ipp64fc, Ipp64f, precision_high_t))

    // abs
    MK2_IPP_REPLACE_TEMPLATE(abs, ippsAbs, , (const Type1* psrc, Type2* pdst, int len, PrecisionType), (psrc, pdst, len), (Type1, Type2, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_2)

#define MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_3(base_struct, base_func, name, desc)  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f, name, desc), (Ipp32f))     \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f, name, desc), (Ipp64f))

#define MK2_IPP_ROUNDING_SIGNATURE (const Type* psrc, Type* pdst, int len)
#define MK2_IPP_ROUNDING_ARGS (psrc, pdst, len)

    MK2_IPP_REPLACE_TEMPLATE(floor,       ippsFloor,     , MK2_IPP_ROUNDING_SIGNATURE, MK2_IPP_ROUNDING_ARGS, (Type), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_3)
    MK2_IPP_REPLACE_TEMPLATE(round,       ippsRound,     , MK2_IPP_ROUNDING_SIGNATURE, MK2_IPP_ROUNDING_ARGS, (Type), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_3)
    MK2_IPP_REPLACE_TEMPLATE(near_by_int, ippsNearbyInt, , MK2_IPP_ROUNDING_SIGNATURE, MK2_IPP_ROUNDING_ARGS, (Type), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_3)
    MK2_IPP_REPLACE_TEMPLATE(r_int,       ippsRint,      , MK2_IPP_ROUNDING_SIGNATURE, MK2_IPP_ROUNDING_ARGS, (Type), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_3)
    MK2_IPP_REPLACE_TEMPLATE(frac,        ippsFrac,      , MK2_IPP_ROUNDING_SIGNATURE, MK2_IPP_ROUNDING_ARGS, (Type), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_3)
    MK2_IPP_REPLACE_TEMPLATE(ceil,        ippsCeil,      , MK2_IPP_ROUNDING_SIGNATURE, MK2_IPP_ROUNDING_ARGS, (Type), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_3)

#undef MK2_IPP_ROUNDING_SIGNATURE
#undef MK2_IPP_ROUNDING_ARGS

#undef MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT
#undef MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT_COMPLEX
#undef MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR
#undef MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_2
#undef MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_3

}}}}