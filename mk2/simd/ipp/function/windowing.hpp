//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp {
namespace function {

#define MK2_IPP_WINDOWING_ASSOCIATOR(base_struct, base_func, name, desc)                    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s,  name, desc), (Ipp16s))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f,  name, desc), (Ipp32f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f,  name, desc), (Ipp64f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16sc, name, desc), (Ipp16sc))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc, name, desc), (Ipp32fc))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc, name, desc), (Ipp64fc))

// common
#define MK2_IPP_WINDOWING_SIGNATURE (const Type* psrc, Type* pdst, int len)
#define MK2_IPP_WINDOWING_ARGS (psrc, pdst, len)

    MK2_IPP_REPLACE_TEMPLATE(win_bartlett, ippsWinBartlett, , MK2_IPP_WINDOWING_SIGNATURE, MK2_IPP_WINDOWING_ARGS, (Type), MK2_IPP_WINDOWING_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(win_blackman, ippsWinBlackman, , MK2_IPP_WINDOWING_SIGNATURE, MK2_IPP_WINDOWING_ARGS, (Type), MK2_IPP_WINDOWING_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(win_hamming,  ippsWinHamming,  , MK2_IPP_WINDOWING_SIGNATURE, MK2_IPP_WINDOWING_ARGS, (Type), MK2_IPP_WINDOWING_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(win_hann,     ippsWinHann,     , MK2_IPP_WINDOWING_SIGNATURE, MK2_IPP_WINDOWING_ARGS, (Type), MK2_IPP_WINDOWING_ASSOCIATOR)

#undef MK2_IPP_WINDOWING_SIGNATURE
#undef MK2_IPP_WINDOWING_ARGS

// inplace
#define MK2_IPP_WINDOWING_I_SIGNATURE (Type* psec_dst, int len)
#define MK2_IPP_WINDOWING_I_ARGS (psec_dst, len)

    MK2_IPP_REPLACE_TEMPLATE(win_bartlett_inplace, ippsWinBartlett, _I, MK2_IPP_WINDOWING_I_SIGNATURE, MK2_IPP_WINDOWING_I_ARGS, (Type), MK2_IPP_WINDOWING_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(win_blackman_inplace, ippsWinBlackman, _I, MK2_IPP_WINDOWING_I_SIGNATURE, MK2_IPP_WINDOWING_I_ARGS, (Type), MK2_IPP_WINDOWING_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(win_hamming_inplace,  ippsWinHamming,  _I, MK2_IPP_WINDOWING_I_SIGNATURE, MK2_IPP_WINDOWING_I_ARGS, (Type), MK2_IPP_WINDOWING_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(win_hann_inplace,     ippsWinHann,     _I, MK2_IPP_WINDOWING_I_SIGNATURE, MK2_IPP_WINDOWING_I_ARGS, (Type), MK2_IPP_WINDOWING_ASSOCIATOR)

#undef MK2_IPP_WINDOWING_I_SIGNATURE
#undef MK2_IPP_WINDOWING_I_ARGS

// kaiser
#define MK2_IPP_WINDOWING_KAISER_ASSOCIATOR(base_struct, base_func, name, desc)                     \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s, name, desc),  (Ipp16s, Ipp32f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f, name, desc),  (Ipp32f, Ipp32f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f, name, desc),  (Ipp64f, Ipp64f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16sc, name, desc), (Ipp16sc, Ipp32f))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc, name, desc), (Ipp32fc, Ipp32f))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc, name, desc), (Ipp64fc, Ipp64f))

    MK2_IPP_REPLACE_TEMPLATE(win_kaiser, ippsWinKaiser, , (const Type* psrc, Type* pdst, int len, AlphaType alpha), (psrc, pdst, len, alpha), (Type, AlphaType), MK2_IPP_WINDOWING_KAISER_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(win_kaiser_inplace, ippsWinKaiser, _I, (Type* psec_dst, int len, AlphaType alpha), (psec_dst, len, alpha), (Type, AlphaType), MK2_IPP_WINDOWING_KAISER_ASSOCIATOR)

#undef MK2_IPP_WINDOWING_ASSOCIATOR
#undef MK2_IPP_WINDOWING_KAISER_ASSOCIATOR

    /*
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)\
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, Ipp16s, base_func##_16s##descriptor, Ipp16s)\
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, Ipp32f, base_func##_32f##descriptor, Ipp32f)\
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, Ipp64f, base_func##_64f##descriptor, Ipp64f)\
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, Ipp16sc, base_func##_16sc##descriptor, Ipp16sc)\
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, Ipp32fc, base_func##_32fc##descriptor, Ipp32fc)\
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, Ipp64fc, base_func##_64fc##descriptor, Ipp64fc)

    // not inplace
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type* pdst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len

    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_bartlett, ippsWinBartlett, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_blackman, ippsWinBlackman, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_hamming, ippsWinHamming, , Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_hann, ippsWinHann, , Type)
    //IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_kaiser, ippsWinKaiser, )
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    // inplace
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    Type* psec_dst, int len
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psec_dst, len

    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_bartlett_inplace, ippsWinBartlett, _I, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_blackman_inplace, ippsWinBlackman, _I, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_hamming_inplace, ippsWinHamming, _I, Type)
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_hann_inplace, ippsWinHann, _I, Type)
    //IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_kaiser_inplace, ippsWinKaiser, _I)

    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS

    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR

    // kaiser
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)\
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, Ipp16s, base_func##_16s##descriptor, Ipp16s, Ipp32f)\
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, Ipp32f, base_func##_32f##descriptor, Ipp32f, Ipp32f)\
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, Ipp64f, base_func##_64f##descriptor, Ipp64f, Ipp64f)\
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, Ipp16sc, base_func##_16sc##descriptor, Ipp16sc, Ipp32f)\
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, Ipp32fc, base_func##_32fc##descriptor, Ipp32fc, Ipp32f)\
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, Ipp64fc, base_func##_64fc##descriptor, Ipp64fc, Ipp64f)

    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type* pdst, int len, AlphaType alpha

    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len, alpha

    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_kaiser, ippsWinKaiser, , Type, AlphaType)

    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS

    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    Type* psec_dst, int len, AlphaType alpha

    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psec_dst, len, alpha

    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_kaiser_inplace, ippsWinKaiser, _I, Type, AlphaType)

    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS

    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR
*/
}}}}