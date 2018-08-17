//
// Created by Himatya on 2018/08/14.
//

#pragma once

#include <array>
#include <cmath>

#include <mk2/container/fixed_array.hpp>
#include <mk2/math/constants.hpp>
#include <mk2/simd/ipp/type.hpp>
#include <mk2/simd/ipp/function/1d/filtering.hpp>

// 双二次フィルタ

namespace mk2 { namespace simd { namespace ipp {
    // coefficients
    template<class Type>
    struct bi_quad_coefficients
    {
        static void all_pass(Type* dst, Type sample_rate, Type freq, Type q)
        {
            Type omega = mk2::math::two_pi<Type> * freq / sample_rate;
            Type alpha = std::sin(omega) / (2 * q);
            
            dst[0] = 1 - alpha;
            dst[1] = - 2 * std::cos(omega);
            dst[2] = 1 + alpha;
            dst[3] = dst[2];
            dst[4] = dst[1];
            dst[5] = dst[0];
        }
    };
    
    template<class Type, int BiQuadOrder = 1>
    class bi_quad_filter
    {
        using state_type = mk2::simd::ipp::ipps_iir_state<Type>;
        
    public:
        bi_quad_filter(Type sample_rate) : sample_rate_(sample_rate)
        {
            int buf_size;
            function::ipps_iir_get_state_size_bi_quad<Type>(BiQuadOrder, &buf_size);
            buffer_ = ippsMalloc_8u(buf_size);
            bi_quad_coefficients<Type>::all_pass(coefficients_.data(), sample_rate, static_cast<Type>(100), mk2::math::int_root_two<Type>);
            function::ipps_iir_init_bi_quad(&state, coefficients_.data(), BiQuadOrder, static_cast<const Type*>(nullptr), buffer_);
        }
    
        ~bi_quad_filter()
        {
            if (buffer_)
                ippsFree(buffer_);
        }
        
        void set_coefficients(const float* cofs)
        {
            function::ipps_copy(cofs, coefficients_.data(), BiQuadOrder * 6);
        }
    
        void process(const Type* src, Type* dst, int len)
        {
            function::ipps_iir(src, dst, len, state);
        }
    
        void process_inplace(Type* src_dst, int len)
        {
            function::ipps_iir_inplace(src_dst, len, state);
        }
        
    private:
        const Type sample_rate_;
        Ipp8u *buffer_;
        state_type *state;
        std::array<Type, BiQuadOrder * 6> coefficients_;
        std::array<Type, BiQuadOrder * 2> delay_;
    };
}}}