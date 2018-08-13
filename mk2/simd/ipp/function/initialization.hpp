//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <ipps.h>

namespace mk2 { namespace simd { namespace ipp { namespace function {
    
    #define IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, type, base_func)                        \
    template<> struct base_struct<type>                                                                                 \
    { template<class ...Args> static IppStatus func(Args&&... args) { return base_func(std::forward<Args>(args)...); }};
    
    #define IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL1(base_struct, base_func, descriptor)          \
    IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp8u, base_func##_8u##descriptor)      \
    IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp16s, base_func##_16s##descriptor)    \
    IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp32s, base_func##_32s##descriptor)    \
    IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp32f, base_func##_32f##descriptor)    \
    IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp64s, base_func##_64s##descriptor)    \
    IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp64f, base_func##_64f##descriptor)    \
    IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp16sc, base_func##_16sc##descriptor)  \
    IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp32sc, base_func##_32sc##descriptor)  \
    IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp32fc, base_func##_32fc##descriptor)  \
    IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp64sc, base_func##_64sc##descriptor)  \
    IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp64fc, base_func##_64fc##descriptor)
    
    #define IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE(func_name, base_func, descriptor)                  \
    namespace detail                                                                                            \
    {                                                                                                           \
        template<class Type> struct func_name##_impl{};                                                         \
        IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL1(func_name##_impl, base_func, descriptor)         \
    }                                                                                                           \
    template<class Type> inline IppStatus func_name(IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE) \
    { return detail::func_name##_impl<Type>::func(IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS); }
    
    // copy and move
    #define IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type* pdst, int len
    
    #define IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len
    
    IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_copy, ippsCopy, )
    IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_move, ippsMove, )
    
    #undef IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    // set
    #define IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    Type val, Type* pdst, int len
    
    #define IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    val, pdst, len
    
    IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_set, ippsSet, )
    
    #undef IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    // zero
    #define IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    Type* pdst, int len
    
    #define IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    pdst, len
    
    IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_zero, ippsZero, )
    
    #undef IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_INITIALIZATION_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
}
}
}
}