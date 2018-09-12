//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <mk2/simd/ipp/type.hpp>
#include <mk2/simd/ipp/function/fft.hpp>

namespace mk2 { namespace simd { namespace ipp {
    template<class Type>
    class fft
    {
        using spec_type = mk2::simd::ipp::ipps_fft_spec_c<Type>;
        
    public:
        fft(int order) : order_(order), fft_spec_(0)
        {
            int size_fft_spec, size_fft_init_buf, size_fft_work_buf;
            
            function::ipps_fft_get_size<spec_type>
                (order_, IPP_FFT_NODIV_BY_ANY, &size_fft_spec, &size_fft_init_buf, &size_fft_work_buf);
    
            Ipp8u* pfft_init_buf;
            pfft_spec_buf_ = ippsMalloc_8u(size_fft_spec);
            pfft_init_buf = ippsMalloc_8u(size_fft_init_buf);
            pfft_work_buf_ = ippsMalloc_8u(size_fft_work_buf);
    
            function::ipps_fft_init(&fft_spec_, order_, IPP_FFT_NODIV_BY_ANY, pfft_spec_buf_, pfft_init_buf);
            if (pfft_init_buf) ippsFree(pfft_init_buf);
        }
        
        ~fft()
        {
            if (pfft_spec_buf_) ippsFree(pfft_spec_buf_);
            if (pfft_work_buf_) ippsFree(pfft_work_buf_);
        }
        
        IppStatus operator()(const Type* src_re, const Type* src_im, Type* dst_re, Type* dst_im)
        {
            return function::ipps_fft_fwd_ctoc(src_re, src_im, dst_re, dst_im, fft_spec_, pfft_work_buf_);
        }
    
        IppStatus inplace(Type* src_dst_re, Type* src_dst_im)
        {
            return function::ipps_fft_fwd_ctoc_inplace(src_dst_re, src_dst_im, fft_spec_, pfft_work_buf_);
        }
        
        IppStatus inverse(const Type* src_re, const Type* src_im, Type* dst_re, Type* dst_im)
        {
            return function::ipps_fft_inv_ctoc(src_re, src_im, dst_re, dst_im, fft_spec_, pfft_work_buf_);
        }
        
        IppStatus inverse_inplace(Type* src_dst_re, Type* src_dst_im)
        {
            return function::ipps_fft_inv_ctoc_inplace(src_dst_re, src_dst_im, fft_spec_, pfft_work_buf_);
        }
        
    private:
        const int order_;
        Ipp8u* pfft_spec_buf_;
        Ipp8u* pfft_work_buf_;
        spec_type *fft_spec_;
    };
}}}