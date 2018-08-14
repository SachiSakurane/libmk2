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
    
    /*
    namespace detail
    {
        template<class ComplexType, class Type> struct ipps_power_spectr_impl{};
        
        template<> struct ipps_power_spectr_impl<Ipp32fc, Ipp32f>
        { template<class ...Args> static IppStatus func(Args&&... args) { return ippsPowerSpectr_32fc(std::forward<Args>(args)...); }};
    
        template<> struct ipps_power_spectr_impl<Ipp64fc, Ipp64f>
        { template<class ...Args> static IppStatus func(Args&&... args) { return ippsPowerSpectr_64fc(std::forward<Args>(args)...); }};
    
        template<> struct ipps_power_spectr_impl<Ipp32f, Ipp32f>
        { template<class ...Args> static IppStatus func(Args&&... args) { return ippsPowerSpectr_32f(std::forward<Args>(args)...); }};
    
        template<> struct ipps_power_spectr_impl<Ipp64f, Ipp64f>
        { template<class ...Args> static IppStatus func(Args&&... args) { return ippsPowerSpectr_64f(std::forward<Args>(args)...); }};
    }
    
    template<class ComplexType, class Type> inline IppStatus ipps_power_spectr(const ComplexType* psrc, Type* pdst, int len)
    { return detail::ipps_power_spectr_impl<ComplexType, Type>::func(psrc, pdst, len); }
    
    template<class Type> inline IppStatus ipps_power_spectr(const Type* psrc_re, const Type* psrc_im, Type* pdst, int len)
    { return detail::ipps_power_spectr_impl<Type, Type>::func(psrc_re, psrc_im, pdst, len); }
    */
}}}}