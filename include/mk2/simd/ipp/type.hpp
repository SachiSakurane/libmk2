//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <ipps.h>

#include <mk2/simd/ipp/type_traits.hpp>

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
    
        template<class type>
        struct ipps_iir_state_impl{};
    
        template<> struct ipps_iir_state_impl<Ipp32f> { using type = IppsIIRState_32f; };
        template<> struct ipps_iir_state_impl<Ipp64f> { using type = IppsIIRState_64f; };
        template<> struct ipps_iir_state_impl<Ipp32fc> { using type = IppsIIRState_32fc; };
        template<> struct ipps_iir_state_impl<Ipp64fc> { using type = IppsIIRState_64fc; };

        template<class type>
        struct ipps_fir_spec_impl{};

        template<> struct ipps_fir_spec_impl<Ipp32f> { using type = IppsFIRSpec_32f; };
        template<> struct ipps_fir_spec_impl<Ipp64f> { using type = IppsFIRSpec_64f; };
        template<> struct ipps_fir_spec_impl<Ipp32fc> { using type = IppsFIRSpec_32fc; };
        template<> struct ipps_fir_spec_impl<Ipp64fc> { using type = IppsFIRSpec_64fc; };
        
        template<class Type>
        struct ipps_complex_impl{};
    
        template<> struct ipps_complex_impl<Ipp32f> { using type = Ipp32fc; };
        template<> struct ipps_complex_impl<Ipp64f> { using type = Ipp64fc; };
        template<> struct ipps_complex_impl<Ipp32fc> { using type = Ipp32fc; };
        template<> struct ipps_complex_impl<Ipp64fc> { using type = Ipp64fc; };

        template <class Type>
        struct ipp_data_type_impl{};

        template<> struct ipp_data_type_impl<Ipp8u>   { static constexpr IppDataType value = IppDataType::ipp8u; };
        template<> struct ipp_data_type_impl<Ipp8s>   { static constexpr IppDataType value = IppDataType::ipp8s; };
        template<> struct ipp_data_type_impl<Ipp8sc>  { static constexpr IppDataType value = IppDataType::ipp8sc; };
        template<> struct ipp_data_type_impl<Ipp16u>  { static constexpr IppDataType value = IppDataType::ipp16u; };
        template<> struct ipp_data_type_impl<Ipp16uc> { static constexpr IppDataType value = IppDataType::ipp16uc; };
        template<> struct ipp_data_type_impl<Ipp16s>  { static constexpr IppDataType value = IppDataType::ipp16s; };
        template<> struct ipp_data_type_impl<Ipp16sc> { static constexpr IppDataType value = IppDataType::ipp16sc; };
        template<> struct ipp_data_type_impl<Ipp32u>  { static constexpr IppDataType value = IppDataType::ipp32u; };
        template<> struct ipp_data_type_impl<Ipp32s>  { static constexpr IppDataType value = IppDataType::ipp32s; };
        template<> struct ipp_data_type_impl<Ipp32sc> { static constexpr IppDataType value = IppDataType::ipp32sc; };
        template<> struct ipp_data_type_impl<Ipp32f>  { static constexpr IppDataType value = IppDataType::ipp32f; };
        template<> struct ipp_data_type_impl<Ipp32fc> { static constexpr IppDataType value = IppDataType::ipp32fc; };
        template<> struct ipp_data_type_impl<Ipp64u>  { static constexpr IppDataType value = IppDataType::ipp64u; };
        template<> struct ipp_data_type_impl<Ipp64s>  { static constexpr IppDataType value = IppDataType::ipp64s; };
        template<> struct ipp_data_type_impl<Ipp64sc> { static constexpr IppDataType value = IppDataType::ipp64sc; };
        template<> struct ipp_data_type_impl<Ipp64f>  { static constexpr IppDataType value = IppDataType::ipp64f; };
        template<> struct ipp_data_type_impl<Ipp64fc> { static constexpr IppDataType value = IppDataType::ipp64fc; };
        
    }
    
    template<class Type>
    using ipps_fft_spec_r = typename detail::ipps_fft_spec_r_impl<Type>::type;
    
    template<class Type>
    using ipps_fft_spec_c = typename detail::ipps_fft_spec_c_impl<Type>::type;

    template<class Type>
    using ipps_fir_spec = typename detail::ipps_fir_spec_impl<Type>::type;

    template<class Type>
    using ipps_iir_state = typename detail::ipps_iir_state_impl<Type>::type;
    
    template<class Type>
    using ipps_complex = typename detail::ipps_complex_impl<Type>::type;

    template <class Type>
    static constexpr IppDataType ipp_data_type = detail::ipp_data_type_impl<Type>::value;


}}}