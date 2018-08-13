//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <ipps.h>

namespace mk2 { namespace simd { namespace ipp { namespace function {
    
    #define IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, type, base_func)                            \
    template<> struct base_struct<type>                                                                                 \
    { template<class ...Args> static IppStatus func(Args&&... args) { return base_func(std::forward<Args>(args)...); }};
                
    #define IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL1(base_struct, base_func, descriptor)          \
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp32f, base_func##_32f##descriptor)    \
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp64f, base_func##_64f##descriptor)    \
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp32fc, base_func##_32fc##descriptor)  \
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL2(base_struct, Ipp64fc, base_func##_64fc##descriptor)
    
    #define IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE(func_name, base_func, descriptor)                  \
    namespace detail                                                                                        \
    {                                                                                                       \
        template<class Type> struct func_name##_impl{};                                                     \
        IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_IMPL1(func_name##_impl, base_func, descriptor)         \
    }                                                                                                       \
    template<class Type> inline IppStatus func_name(IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE) \
    { return detail::func_name##_impl<Type>::func(IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS); }
    
    
    // not inplace
    #define IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc1, const Type* psrc2, Type* pdst, int len
    
    #define IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc1, psrc2, pdst, len
    
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_add, ippsAdd,)
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_sub, ippsSub,)
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_mul, ippsMul,)
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_div, ippsDiv,)
    
    #undef IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    
    // inplace
    #define IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type* psrc_dst, int len
    
    #define IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, psrc_dst, len
    
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_add_inplace, ippsAdd, _I)
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_sub_inplace, ippsSub, _I)
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_mul_inplace, ippsMul, _I)
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_div_inplace, ippsDiv, _I)
    
    #undef IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    // c not inplace
    #define IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type val, Type* pdst, int len
    
    #define IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, val, pdst, len
    
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_addc, ippsAddC, )
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_subc, ippsSubC, )
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_mulc, ippsMulC, )
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_divc, ippsDivC, )
    
    #undef IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    // c inplace
    #define IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    Type val, Type* psrc_dst, int len
    
    #define IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    val, psrc_dst, len
    
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_addc_inplace, ippsAddC, _I)
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_subc_inplace, ippsSubC, _I)
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_mulc_inplace, ippsMulC, _I)
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_divc_inplace, ippsDivC, _I)
    
    #undef IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    // arithmetic not inplace
    #define IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    const Type* psrc, Type* pdst, int len
    
    #define IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc, pdst, len
    
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_sqrt, ippsSqrt, )
    
    #undef IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    // arithmetic inplace
    #define IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    Type* psrc_dst, int len
    
    #define IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    psrc_dst, len
    
    IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_sqrt_inplace, ippsSqrt, _I)
    
    #undef IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_ARITHMETIC_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS


}}}}