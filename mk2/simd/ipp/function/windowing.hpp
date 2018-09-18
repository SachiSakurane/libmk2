//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp { namespace function {

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

}}}}