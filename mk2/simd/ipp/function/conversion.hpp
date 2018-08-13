//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <ipps.h>

namespace mk2 { namespace simd { namespace ipp { namespace function {
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
}}}}