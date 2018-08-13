//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <ipps.h>

namespace mk2 { namespace simd { namespace ipp { namespace function {
    
    // ipps_fft_init
    namespace detail
    {
        template<class IppsFFTSpec>
        inline IppStatus ipps_fft_init_impl(IppsFFTSpec**, int, int, IppHintAlgorithm, Ipp8u*, Ipp8u*);
    
        template<> inline IppStatus ipps_fft_init_impl<IppsFFTSpec_R_32f>
            (IppsFFTSpec_R_32f** ppfft_spec, int order, int flag, IppHintAlgorithm hint, Ipp8u* pspec, Ipp8u* pspec_buffer)
        { return ippsFFTInit_R_32f(ppfft_spec, order, flag, hint, pspec, pspec_buffer); }
    
        template<> inline IppStatus ipps_fft_init_impl<IppsFFTSpec_R_64f>
            (IppsFFTSpec_R_64f** ppfft_spec, int order, int flag, IppHintAlgorithm hint, Ipp8u* pspec, Ipp8u* pspec_buffer)
        { return ippsFFTInit_R_64f(ppfft_spec, order, flag, hint, pspec, pspec_buffer); }
    
        template<> inline IppStatus ipps_fft_init_impl<IppsFFTSpec_C_32f>
            (IppsFFTSpec_C_32f** ppfft_spec, int order, int flag, IppHintAlgorithm hint, Ipp8u* pspec, Ipp8u* pspec_buffer)
        { return ippsFFTInit_C_32f(ppfft_spec, order, flag, hint, pspec, pspec_buffer); }
    
        template<> inline IppStatus ipps_fft_init_impl<IppsFFTSpec_C_64f>
            (IppsFFTSpec_C_64f** ppfft_spec, int order, int flag, IppHintAlgorithm hint, Ipp8u* pspec, Ipp8u* pspec_buffer)
        { return ippsFFTInit_C_64f(ppfft_spec, order, flag, hint, pspec, pspec_buffer); }
    
        template<> inline IppStatus ipps_fft_init_impl<IppsFFTSpec_C_32fc>
            (IppsFFTSpec_C_32fc** ppfft_spec, int order, int flag, IppHintAlgorithm hint, Ipp8u* pspec, Ipp8u* pspec_buffer)
        { return ippsFFTInit_C_32fc(ppfft_spec, order, flag, hint, pspec, pspec_buffer); }
    
        template<> inline IppStatus ipps_fft_init_impl<IppsFFTSpec_C_64fc>
            (IppsFFTSpec_C_64fc** ppfft_spec, int order, int flag, IppHintAlgorithm hint, Ipp8u* pspec, Ipp8u* pspec_buffer)
        { return ippsFFTInit_C_64fc(ppfft_spec, order, flag, hint, pspec, pspec_buffer); }
    }
    
    template<class IppsFFTSpec> inline IppStatus ipps_fft_init
        (IppsFFTSpec** ppfft_spec, int order, int flag, Ipp8u* pspec, Ipp8u* pspec_buffer)
    { return detail::ipps_fft_init_impl(ppfft_spec, order, flag, ippAlgHintNone, pspec, pspec_buffer); }
    
    // ipps_fft_get_size
    namespace detail
    {
        template<class IppsFFTSpec>
        inline IppStatus ipps_fft_get_size_impl(int order, int flag, IppHintAlgorithm hint, int* pspec_size, int* pspec_buffer_size, int* pbuffer_size);
    
        template<> inline IppStatus ipps_fft_get_size_impl<IppsFFTSpec_R_32f>
            (int order, int flag, IppHintAlgorithm hint, int* pspec_size, int* pspec_buffer_size, int* pbuffer_size)
        { return ippsFFTGetSize_R_32f(order, flag, hint, pspec_size, pspec_buffer_size, pbuffer_size); }
    
        template<> inline IppStatus ipps_fft_get_size_impl<IppsFFTSpec_R_64f>
            (int order, int flag, IppHintAlgorithm hint, int* pspec_size, int* pspec_buffer_size, int* pbuffer_size)
        { return ippsFFTGetSize_R_64f(order, flag, hint, pspec_size, pspec_buffer_size, pbuffer_size); }
    
        template<> inline IppStatus ipps_fft_get_size_impl<IppsFFTSpec_C_32f>
            (int order, int flag, IppHintAlgorithm hint, int* pspec_size, int* pspec_buffer_size, int* pbuffer_size)
        { return ippsFFTGetSize_C_32f(order, flag, hint, pspec_size, pspec_buffer_size, pbuffer_size); }
    
        template<> inline IppStatus ipps_fft_get_size_impl<IppsFFTSpec_C_64f>
            (int order, int flag, IppHintAlgorithm hint, int* pspec_size, int* pspec_buffer_size, int* pbuffer_size)
        { return ippsFFTGetSize_C_64f(order, flag, hint, pspec_size, pspec_buffer_size, pbuffer_size); }
    
        template<> inline IppStatus ipps_fft_get_size_impl<IppsFFTSpec_C_32fc>
            (int order, int flag, IppHintAlgorithm hint, int* pspec_size, int* pspec_buffer_size, int* pbuffer_size)
        { return ippsFFTGetSize_C_32fc(order, flag, hint, pspec_size, pspec_buffer_size, pbuffer_size); }
    
        template<> inline IppStatus ipps_fft_get_size_impl<IppsFFTSpec_C_64fc>
            (int order, int flag, IppHintAlgorithm hint, int* pspec_size, int* pspec_buffer_size, int* pbuffer_size)
        { return ippsFFTGetSize_C_64fc(order, flag, hint, pspec_size, pspec_buffer_size, pbuffer_size); }
    }
    
    template<class IppsFFTSpec> inline IppStatus ipps_fft_get_size
        (int order, int flag, int* pspec_size, int* pspec_buffer_size, int* pbuffer_size)
    { return detail::ipps_fft_get_size_impl<IppsFFTSpec>(order, flag, ippAlgHintNone, pspec_size, pspec_buffer_size, pbuffer_size); }
    

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