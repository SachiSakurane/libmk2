//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <type_traits>
#include <ipps.h>

namespace mk2 { namespace simd { namespace ipp {

    namespace detail
    {
        template<class Type>
        struct is_ipp_complex_impl { using value = std::false_type; };
    
        template<> struct is_ipp_complex_impl<Ipp32fc> { using value = std::true_type; };
        template<> struct is_ipp_complex_impl<Ipp64fc> { using value = std::true_type; };
    }
    
    template<class Type> struct is_ipp_complex : public detail::is_ipp_complex_impl<Type>{};
}}}