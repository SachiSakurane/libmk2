//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <memory>

#include <mk2/simd/ipp/ipp_buffer_delete.hpp>
#include <mk2/simd/ipp/type.hpp>
#include <mk2/simd/ipp/function/fft.hpp>

namespace mk2 { namespace simd { namespace ipp {
    template<class Type>
    class fft
    {
        using ptr_type = std::unique_ptr<Ipp8u, mk2::simd::ipp::ipp_buffer_delete<Ipp8u>>;
        using spec_type = mk2::simd::ipp::ipps_fft_spec_c<Type>;
        
    public:
        fft(int order) : order_(order), fft_spec_(0)
        {
            int size_fft_spec, size_fft_init_buf, size_fft_work_buf;

            mk2::simd::ipp::function::fft_get_size<spec_type>
                (order_, IPP_FFT_NODIV_BY_ANY, &size_fft_spec, &size_fft_init_buf, &size_fft_work_buf);
    
            ptr_type pfft_init_buf;
            pfft_spec_buf_ = ippsMalloc_8u(size_fft_spec);
            pfft_init_buf  = ippsMalloc_8u(size_fft_init_buf);
            pfft_work_buf_ = ippsMalloc_8u(size_fft_work_buf);

            mk2::simd::ipp::function::fft_init(&fft_spec_, order_, IPP_FFT_NODIV_BY_ANY, pfft_spec_buf_.get(), pfft_init_buf.get());
        }
        
        ~fft() = default;
        
        IppStatus forward(const Type* src_re, const Type* src_im, Type* dst_re, Type* dst_im)
        {
            return mk2::simd::ipp::function::fft_fwd_ctoc(src_re, src_im, dst_re, dst_im, fft_spec_, pfft_work_buf_.get());
        }
    
        IppStatus forward_inplace(Type* src_dst_re, Type* src_dst_im)
        {
            return mk2::simd::ipp::function::fft_fwd_ctoc_inplace(src_dst_re, src_dst_im, fft_spec_, pfft_work_buf_.get());
        }
        
        IppStatus inverse(const Type* src_re, const Type* src_im, Type* dst_re, Type* dst_im)
        {
            return mk2::simd::ipp::function::fft_inv_ctoc(src_re, src_im, dst_re, dst_im, fft_spec_, pfft_work_buf_.get());
        }
        
        IppStatus inverse_inplace(Type* src_dst_re, Type* src_dst_im)
        {
            return mk2::simd::ipp::function::fft_inv_ctoc_inplace(src_dst_re, src_dst_im, fft_spec_, pfft_work_buf_.get());
        }
        
    private:
        const int order_;
        ptr_type Ipp8u pfft_spec_buf_;
        ptr_type Ipp8u pfft_work_buf_;
        spec_type *fft_spec_;
    };
}}}