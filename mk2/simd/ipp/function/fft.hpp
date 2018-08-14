//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <ipps.h>

#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp { namespace function {
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor)                \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_R_32f##descriptor, IppsFFTSpec_R_32f)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_R_64f##descriptor, IppsFFTSpec_R_64f)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_C_32f##descriptor, IppsFFTSpec_C_32f)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_C_64f##descriptor, IppsFFTSpec_C_64f)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_C_32fc##descriptor, IppsFFTSpec_C_32fc)   \
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_C_64fc##descriptor, IppsFFTSpec_C_64fc)
                
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    IppsFFTSpec** ppfft_spec, int order, int flag, Ipp8u* pspec, Ipp8u* pspec_buffer
                
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    ppfft_spec, order, flag, ippAlgHintNone, pspec, pspec_buffer
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_fft_init, ippsFFTInit, , IppsFFTSpec)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE \
    int order, int flag, int* pspec_size, int* pspec_buffer_size, int* pbuffer_size
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS   \
    order, flag, ippAlgHintNone, pspec_size, pspec_buffer_size, pbuffer_size
    
    IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(ipps_fft_get_size, ippsFFTGetSize, , IppsFFTSpec)
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS
    
    #undef IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR

    namespace detail
    {
        template<class Type, class IppsFFTSpec>
        inline IppStatus ipps_fft_fwd_ctoc_impl
            (const Type* psrc_re, const Type* psrc_im, Type* pdst_re, Type* pdst_im, const IppsFFTSpec* pfft_spec, Ipp8u* pbuffer);
        
        template<> inline IppStatus ipps_fft_fwd_ctoc_impl<Ipp32f, IppsFFTSpec_C_32f>
            (const Ipp32f* psrc_re, const Ipp32f* psrc_im, Ipp32f* pdst_re, Ipp32f* pdst_im, const IppsFFTSpec_C_32f* pfft_spec, Ipp8u* pbuffer)
        { return ippsFFTFwd_CToC_32f(psrc_re, psrc_im, pdst_re, pdst_im, pfft_spec, pbuffer); }
    
        template<> inline IppStatus ipps_fft_fwd_ctoc_impl<Ipp64f, IppsFFTSpec_C_64f>
            (const Ipp64f* psrc_re, const Ipp64f* psrc_im, Ipp64f* pdst_re, Ipp64f* pdst_im, const IppsFFTSpec_C_64f* pfft_spec, Ipp8u* pbuffer)
        { return ippsFFTFwd_CToC_64f(psrc_re, psrc_im, pdst_re, pdst_im, pfft_spec, pbuffer); }
    
        template<class Type, class IppsFFTSpec>
        inline IppStatus ipps_fft_fwd_ctoc_impl
            (const Type* psrc, Type* pdst, const IppsFFTSpec* pfft_spec, Ipp8u* pbuffer);
    
        template<> inline IppStatus ipps_fft_fwd_ctoc_impl<Ipp32fc, IppsFFTSpec_C_32fc>
            (const Ipp32fc* psrc, Ipp32fc* pdst, const IppsFFTSpec_C_32fc* pfft_spec, Ipp8u* pbuffer)
        { return ippsFFTFwd_CToC_32fc(psrc, pdst, pfft_spec, pbuffer); }
    
        template<> inline IppStatus ipps_fft_fwd_ctoc_impl<Ipp64fc, IppsFFTSpec_C_64fc>
            (const Ipp64fc* psrc, Ipp64fc* pdst, const IppsFFTSpec_C_64fc* pfft_spec, Ipp8u* pbuffer)
        { return ippsFFTFwd_CToC_64fc(psrc, pdst, pfft_spec, pbuffer); }
    
        template<class Type, class IppsFFTSpec>
        inline IppStatus ipps_fft_fwd_ctoc_inplace_impl
            (Type* psrc_dst_re, Type* psrc_dst_im, const IppsFFTSpec* pfft_spec, Ipp8u* pbuffer);
        
        template<> inline IppStatus ipps_fft_fwd_ctoc_inplace_impl<Ipp32f, IppsFFTSpec_C_32f>
            (Ipp32f* psrc_dst_re, Ipp32f* psrc_dst_im, const IppsFFTSpec_C_32f* pfft_spec, Ipp8u* pbuffer)
        { return ippsFFTFwd_CToC_32f_I(psrc_dst_re, psrc_dst_im, pfft_spec, pbuffer); }
        
        template<> inline IppStatus ipps_fft_fwd_ctoc_inplace_impl<Ipp64f, IppsFFTSpec_C_64f>
            (Ipp64f* psrc_dst_re, Ipp64f* psrc_dst_im, const IppsFFTSpec_C_64f* pfft_spec, Ipp8u* pbuffer)
        { return ippsFFTFwd_CToC_64f_I(psrc_dst_re, psrc_dst_im, pfft_spec, pbuffer); }
    }
    
    // fft_fwd_ctoc
    template<class Type, class IppsFFTSpec> inline IppStatus ipps_fft_fwd_ctoc
        (const Type* psrc_re, const Type* psrc_im, Type* pdst_re, Type* pdst_im, const IppsFFTSpec* pfft_spec, Ipp8u* pbuffer)
    { return detail::ipps_fft_fwd_ctoc_impl(psrc_re, psrc_im, pdst_re, pdst_im, pfft_spec, pbuffer); }
    
    template<class Type, class IppsFFTSpec> inline IppStatus ipps_fft_fwd_ctoc
        (const Type* psrc, Type* pdst, const IppsFFTSpec* pfft_spec, Ipp8u* pbuffer)
    { return detail::ipps_fft_fwd_ctoc_impl(psrc, pdst, pfft_spec, pbuffer); }
    
    // fft_fwd_ctoc implace
    template<class Type, class IppsFFTSpec> inline IppStatus ipps_fft_fwd_ctoc_inplace
        (Type* psrc_dst_re, Type* psrc_dst_im, const IppsFFTSpec* pfft_spec, Ipp8u* pbuffer)
    { return detail::ipps_fft_fwd_ctoc_inplace_impl(psrc_dst_re, psrc_dst_im, pfft_spec, pbuffer); }
    
}}}}