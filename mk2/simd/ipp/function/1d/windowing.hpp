//
// Created by Himatya on 2018/08/13.
//

#pragma once

namespace mk2 { namespace simd { namespace ipp { namespace function {
    
    #define IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, type, base_func)                            \
    template<> struct base_struct<type>                                                                                 \
    { template<class ...Args> static IppStatus func(Args&&... args) { return base_func(std::forward<Args>(args)...); }};
                
    #define IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL1(base_struct, base_func, descriptor)          \
    IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp16s, base_func##_16s##descriptor)    \
    IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp16sc, base_func##_16sc##descriptor)    \
    IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp32f, base_func##_32f##descriptor)    \
    IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp64f, base_func##_64f##descriptor)    \
    IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp32fc, base_func##_32fc##descriptor)  \
    IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp64fc, base_func##_64fc##descriptor)
                
    #define IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE(func_name, base_func, descriptor)                  \
    namespace detail                                                                                        \
    {                                                                                                       \
        template<class Type> struct func_name##_impl{};                                                     \
        IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL1(func_name##_impl, base_func, descriptor)         \
    }                                                                                                       \
    template<class Type> inline IppStatus func_name(IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE) \
    { return detail::func_name##_impl<Type>::func(IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS); }
    
    // not inplace
    #define IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type* pdst, int len
    
    #define IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len
    
    IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_bartlett, ippsWinBartlett, )
    IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_blackman, ippsWinBlackman, )
    IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_hamming, ippsWinHamming, )
    IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_hann, ippsWinHann, )
    IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_kaiser, ippsWinKaiser, )
    
    #undef IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    // inplace
    #define IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    Type* psec_dst, int len
    
    #define IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psec_dst, len
    
    IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_bartlett_inplace, ippsWinBartlett, _I)
    IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_blackman_inplace, ippsWinBlackman, _I)
    IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_hamming_inplace, ippsWinHamming, _I)
    IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_hann_inplace, ippsWinHann, _I)
    IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_win_kaiser_inplace, ippsWinKaiser, _I)
    
    #undef IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_WINDOWING_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
}}}}