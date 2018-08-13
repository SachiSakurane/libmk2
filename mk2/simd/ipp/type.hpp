//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <ipps.h>

namespace mk2 { namespace simd { namespace ipp {
    namespace detail
    {
        template<class type>
        struct ipps_fft_spec_r_impl{};
    
        template<> struct ipps_fft_spec_r_impl<Ipp32f> { using type = IppsFFTSpec_R_32f; };
        template<> struct ipps_fft_spec_r_impl<Ipp64f> { using type = IppsFFTSpec_R_64f; };
    
        template<class type>
        struct ipps_fft_spec_c_impl{};
    
        template<> struct ipps_fft_spec_c_impl<Ipp32f> { using type = IppsFFTSpec_C_32f; };
        template<> struct ipps_fft_spec_c_impl<Ipp64f> { using type = IppsFFTSpec_C_64f; };
        template<> struct ipps_fft_spec_c_impl<Ipp32fc> { using type = IppsFFTSpec_C_32fc; };
        template<> struct ipps_fft_spec_c_impl<Ipp64fc> { using type = IppsFFTSpec_C_64fc; };
    }
    
    template<class Type>
    using ipps_fft_spec_r = typename detail::ipps_fft_spec_r_impl<Type>::type;
    
    template<class Type>
    using ipps_fft_spec_c = typename detail::ipps_fft_spec_c_impl<Type>::type;
}}}