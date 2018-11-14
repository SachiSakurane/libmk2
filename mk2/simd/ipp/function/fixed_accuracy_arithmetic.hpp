//
// Created by Himatya on 2018/08/17.
//

#pragma once

#include <ipp.h>

#include <mk2/simd/ipp/function/float_precision.hpp>
#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp {
namespace function {
#define MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT(base_struct, base_func, name, desc)              \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f_A11, name, desc), (Ipp32f, precision_low))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f_A21, name, desc), (Ipp32f, precision_mid))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f_A24, name, desc), (Ipp32f, precision_high)) \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f_A26, name, desc), (Ipp64f, precision_low))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f_A50, name, desc), (Ipp64f, precision_mid))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f_A53, name, desc), (Ipp64f, precision_high))

#define MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT_COMPLEX(base_struct, base_func, name, desc)          \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc_A11, name, desc), (Ipp32fc, precision_low))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc_A21, name, desc), (Ipp32fc, precision_mid))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc_A24, name, desc), (Ipp32fc, precision_high))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc_A26, name, desc), (Ipp64fc, precision_low))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc_A50, name, desc), (Ipp64fc, precision_mid))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc_A53, name, desc), (Ipp64fc, precision_high))

#define MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR(base_struct, base_func, name, desc)    \
    MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT(base_struct, base_func, name, desc)  \
    MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_FLOAT_COMPLEX(base_struct, base_func, name, desc)

    // pow
    MK2_IPP_REPLACE_TEMPLATE(pow, ippsPow, , (const Type* psrc1, const Type* psrc2, Type* pdst, Ipp32s len, PrecisionType), (psrc1, psrc2, pdst, len), (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)

    // powx
    MK2_IPP_REPLACE_TEMPLATE(powx, ippsPowx, , (const Type* psrc1, const Type ConstValue, Type* pdst, Ipp32s len, PrecisionType), (psrc1, ConstValue, pdst, len), (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)

    // ln
    MK2_IPP_REPLACE_TEMPLATE(ln, ippsLn, , (const Type* psrc, Type* pdst, Ipp32s len, PrecisionType), (psrc, pdst, len), (Type, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR)

#define MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_2(base_struct, base_func, name, desc)                              \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f_A24,  name, desc), (Ipp32f, Ipp32f, precision_high))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f_A53,  name, desc), (Ipp64f, Ipp32f, precision_high))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc_A11, name, desc), (Ipp32fc, Ipp32f, precision_low))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc_A21, name, desc), (Ipp32fc, Ipp32f, precision_mid))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc_A24, name, desc), (Ipp32fc, Ipp32f, precision_high))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc_A26, name, desc), (Ipp64fc, Ipp64f, precision_low))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc_A50, name, desc), (Ipp64fc, Ipp64f, precision_mid))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc_A53, name, desc), (Ipp64fc, Ipp64f, precision_high))

    // abs
    MK2_IPP_REPLACE_TEMPLATE(abs, ippsAbs, , (const Type1* psrc, Type2* pdst, int len, PrecisionType), (psrc, pdst, len), (Type1, Type2, PrecisionType), MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_2)

#define MK2_IPP_FIXED_ACCURACY_ARITHMETIC_ASSOCIATOR_3(base_struct, base_func, name, desc)  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f, name, desc), (Ipp32f))     \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f, name, desc), (Ipp64f))

#define MK2_IPP_ROUNDING_SIGNATURE (const Type* psrc, Type* pdst, int len)
#define MK2_IPP_ROUNDING_ARGS (psrc, pdst, len)

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

    /*
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC_ALL_PRECISION(base_struct, base_func, descriptor)            \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f_A11##descriptor, Ipp32f, precision_low) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f_A21##descriptor, Ipp32f, precision_mid) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f_A24##descriptor, Ipp32f, precision_high)\
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f_A26##descriptor, Ipp64f, precision_low) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f_A50##descriptor, Ipp64f, precision_mid) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f_A53##descriptor, Ipp64f, precision_high)
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC_ALL_PRECISION_COMPLEX(base_struct, base_func, descriptor)        \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc_A11##descriptor, Ipp32fc, precision_low)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc_A21##descriptor, Ipp32fc, precision_mid)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc_A24##descriptor, Ipp32fc, precision_high)  \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc_A26##descriptor, Ipp64fc, precision_low)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc_A50##descriptor, Ipp64fc, precision_mid)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc_A53##descriptor, Ipp64fc, precision_high)
    
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)             \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC_ALL_PRECISION(base_struct, base_func, descriptor)             \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC_ALL_PRECISION_COMPLEX(base_struct, base_func, descriptor)
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc1, const Type* psrc2, Type* pdst, Ipp32s len, PrecisionType
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc1, psrc2, pdst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_pow, ippsPow, , Type, PrecisionType)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS


    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc1, const Type ConstValue, Type* pdst, Ipp32s len, PrecisionType

    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc1, ConstValue, pdst, len

    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_powx, ippsPowx, , Type, PrecisionType)

    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS


    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type* pdst, Ipp32s len, PrecisionType

    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len

    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_ln, ippsLn, , Type, PrecisionType)

    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS

    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR
    
    */
    /*
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor) \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f_A24##descriptor, Ipp32f, Ipp32f, precision_high)\
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f_A53##descriptor, Ipp64f, Ipp32f, precision_high)\
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc_A11##descriptor, Ipp32fc, Ipp32f, precision_low)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc_A21##descriptor, Ipp32fc, Ipp32f, precision_mid)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc_A24##descriptor, Ipp32fc, Ipp32f, precision_high)  \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc_A26##descriptor, Ipp64fc, Ipp64f, precision_low)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc_A50##descriptor, Ipp64fc, Ipp64f, precision_mid)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc_A53##descriptor, Ipp64fc, Ipp64f, precision_high)
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type1* psrc, Type2* pdst, int len, PrecisionType
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_abs, ippsAbs, , Type1, Type2, PrecisionType)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR

    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f##descriptor, Ipp32f)    \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f##descriptor, Ipp64f)
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type* pdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len

    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_round, ippsRound, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_near_by_int, ippsNearbyInt, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_r_int, ippsRint, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_frac, ippsFrac, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_ceil, ippsCeil, , Type)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR

    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC_ALL_PRECISION
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC_ALL_PRECISION_COMPLEX
    */
}}}}