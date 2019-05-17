//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <mk2/simd/ipp/include.hpp>
#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp {
namespace function {

#define MK2_IPP_FFT_INIT_ASSOCIATOR(base_struct, base_func, name, desc)                                 \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_R_32f,  name, desc), (IppsFFTSpec_R_32f))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_R_64f,  name, desc), (IppsFFTSpec_R_64f))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_C_32f,  name, desc), (IppsFFTSpec_C_32f))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_C_64f,  name, desc), (IppsFFTSpec_C_64f))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_C_32fc, name, desc), (IppsFFTSpec_C_32fc))  \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_C_64fc, name, desc), (IppsFFTSpec_C_64fc))

    // init
    MK2_IPP_REPLACE_TEMPLATE(fft_init, ippsFFTInit, , (IppsFFTSpec** ppfft_spec, int order, int flag, Ipp8u* pspec, Ipp8u* pspec_buffer), (ppfft_spec, order, flag, ippAlgHintNone, pspec, pspec_buffer), (IppsFFTSpec), MK2_IPP_FFT_INIT_ASSOCIATOR)

    // get size
    MK2_IPP_REPLACE_TEMPLATE(fft_get_size, ippsFFTGetSize, , (int order, int flag, int* pspec_size, int* pspec_buffer_size, int* pbuffer_size), (order, flag, ippAlgHintNone, pspec_size, pspec_buffer_size, pbuffer_size), (IppsFFTSpec), MK2_IPP_FFT_INIT_ASSOCIATOR)

#undef MK2_IPP_FFT_INIT_ASSOCIATOR

#define MK2_IPP_FFT_ASSOCIATOR_FLOAT(base_struct, base_func, name, desc)                                        \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f,  name, desc), (Ipp32f,  IppsFFTSpec_C_32f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f,  name, desc), (Ipp64f,  IppsFFTSpec_C_64f))

#define MK2_IPP_FFT_ASSOCIATOR_COMPLEX(base_struct, base_func, name, desc)                                      \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc, name, desc), (Ipp32fc, IppsFFTSpec_C_32fc))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc, name, desc), (Ipp64fc, IppsFFTSpec_C_64fc))

    // real
    MK2_IPP_REPLACE_TEMPLATE(fft_fwd_ctoc, ippsFFTFwd_CToC, , (const Type* psrc_re, const Type* psrc_im, Type* pdst_re, Type* pdst_im, const IppsFFTSpec* pfft_spec, Ipp8u* pbuffer), (psrc_re, psrc_im, pdst_re, pdst_im, pfft_spec, pbuffer), (Type, IppsFFTSpec), MK2_IPP_FFT_ASSOCIATOR_FLOAT)
    MK2_IPP_REPLACE_TEMPLATE(fft_inv_ctoc, ippsFFTInv_CToC, , (const Type* psrc_re, const Type* psrc_im, Type* pdst_re, Type* pdst_im, const IppsFFTSpec* pfft_spec, Ipp8u* pbuffer), (psrc_re, psrc_im, pdst_re, pdst_im, pfft_spec, pbuffer), (Type, IppsFFTSpec), MK2_IPP_FFT_ASSOCIATOR_FLOAT)
    MK2_IPP_REPLACE_TEMPLATE_ADDITIVE(fft_fwd_ctoc, ippsFFTFwd_CToC, , (const Type* psrc, Type* pdst, const IppsFFTSpec* pfft_spec, Ipp8u* pbuffer), (psrc, pdst, pfft_spec, pbuffer), (Type, IppsFFTSpec), MK2_IPP_FFT_ASSOCIATOR_COMPLEX)
    MK2_IPP_REPLACE_TEMPLATE_ADDITIVE(fft_inv_ctoc, ippsFFTInv_CToC, , (const Type* psrc, Type* pdst, const IppsFFTSpec* pfft_spec, Ipp8u* pbuffer), (psrc, pdst, pfft_spec, pbuffer), (Type, IppsFFTSpec), MK2_IPP_FFT_ASSOCIATOR_COMPLEX)

    // inplace
    MK2_IPP_REPLACE_TEMPLATE(fft_fwd_ctoc_inplace, ippsFFTFwd_CToC, _I, (Type* psrc_dst_re, Type* psrc_dst_im, const IppsFFTSpec* pfft_spec, Ipp8u* pbuffer), (psrc_dst_re, psrc_dst_im, pfft_spec, pbuffer), (Type, IppsFFTSpec), MK2_IPP_FFT_ASSOCIATOR_FLOAT)
    MK2_IPP_REPLACE_TEMPLATE(fft_inv_ctoc_inplace, ippsFFTInv_CToC, _I, (Type* psrc_dst_re, Type* psrc_dst_im, const IppsFFTSpec* pfft_spec, Ipp8u* pbuffer), (psrc_dst_re, psrc_dst_im, pfft_spec, pbuffer), (Type, IppsFFTSpec), MK2_IPP_FFT_ASSOCIATOR_FLOAT)
    MK2_IPP_REPLACE_TEMPLATE_ADDITIVE(fft_fwd_ctoc_inplace, ippsFFTFwd_CToC, _I, (Type* psrcdst, const IppsFFTSpec* pfft_spec, Ipp8u* pbuffer), (psrcdst, pfft_spec, pbuffer), (Type, IppsFFTSpec), MK2_IPP_FFT_ASSOCIATOR_COMPLEX)
    MK2_IPP_REPLACE_TEMPLATE_ADDITIVE(fft_inv_ctoc_inplace, ippsFFTInv_CToC, _I, (Type* psrcdst, const IppsFFTSpec* pfft_spec, Ipp8u* pbuffer), (psrcdst, pfft_spec, pbuffer), (Type, IppsFFTSpec), MK2_IPP_FFT_ASSOCIATOR_COMPLEX)


#undef MK2_IPP_FFT_ASSOCIATOR_FLOAT
#undef MK2_IPP_FFT_ASSOCIATOR_COMPLEX

}}}}