//
// Created by Himatya on 2018/08/14.
//

#pragma once

#include <array>
#include <cmath>
#include <memory>

#include <mk2/container/fixed_array.hpp>
#include <mk2/math/constants.hpp>
#include <mk2/simd/ipp/ipp_buffer_delete.hpp>
#include <mk2/simd/ipp/type.hpp>
#include <mk2/simd/ipp/function/filtering.hpp>
#include <mk2/simd/ipp/function/initialization.hpp>

// 双二次フィルタ

namespace mk2 { namespace simd { namespace ipp {

    // sample rate, freq, q -> lambda(dst)を返すような感じ？
    namespace bi_quad_coefficients
    {
        template <class Type>
        decltype(auto) all_pass(Type freq, Type q)
        {
            return [freq, q](Type sample_rate, Type* dst)
            {
                const Type omega = mk2::math::two_pi<Type> * freq / sample_rate;
                const Type alpha = std::sin(omega) / (2 * q);

                dst[0] = 1 - alpha;
                dst[1] = - 2 * std::cos(omega);
                dst[2] = 1 + alpha;
                dst[3] = dst[2];
                dst[4] = dst[1];
                dst[5] = dst[0];
            };
        }

        template <class Type>
        decltype(auto) low_pass(Type freq, Type q)
        {
            return [freq, q](Type sample_rate, Type* dst)
            {
                const Type omega = mk2::math::two_pi<Type> * freq / sample_rate;
                const Type cosw = std::cos(omega);
                const Type rcosw = 1 - cosw;
                const Type alpha = std::sin(omega) / (static_cast<Type>(2) * q);


                dst[0] = rcosw / 2;
                dst[1] = rcosw;
                dst[2] = dst[0];
                dst[3] = 1 + alpha;
                dst[4] = - 2 * cosw;
                dst[5] = 1 - alpha;
            };
        }

        template <class Type>
        decltype(auto) high_pass(Type freq, Type q)
        {
            return [freq, q](Type sample_rate, Type* dst)
            {
                const Type omega = mk2::math::two_pi<Type> * freq / sample_rate;
                const Type cosw = std::cos(omega);
                const Type rcosw = 1 + cosw;
                const Type alpha = std::sin(omega) / (static_cast<Type>(2) * q);

                dst[0] = rcosw / 2;
                dst[1] = -rcosw;
                dst[2] = dst[0];
                dst[3] = 1 + alpha;
                dst[4] = - 2 * cosw;
                dst[5] = 1 - alpha;
            };
        }

        template <class Type>
        decltype(auto) low_shelf(Type freq, Type q, Type dB)
        {
            return [freq, q, dB](Type sample_rate, Type* dst)
            {
                const Type omega = mk2::math::two_pi<Type> * freq / sample_rate;
                const Type cosw = std::cos(omega);
                const Type rcosw = 1 + cosw;
                const Type alpha = std::sin(omega) / (static_cast<Type>(2) * q);
                const Type A = std::pow (static_cast<Type>(10), dB * static_cast<Type>(0.025));
                const Type rA = A - 1;
                const Type fA = A + 1;
                const Type x = fA + rA * cosw;
                const Type y = fA - rA * cosw;
                const Type sa2 = 2 * std::sqrt(A) * alpha;

                dst[0] = A * (y + sa2);
                dst[1] = 2 * A * (rA - fA * cosw);
                dst[2] = A * (y - sa2);
                dst[3] = x + sa2;
                dst[4] = - 2 * (rA + fA * cosw);
                dst[5] = x - sa2;
            };
        }

        template <class Type>
        decltype(auto) high_shelf(Type freq, Type q, Type dB)
        {
            return [freq, q, dB](Type sample_rate, Type* dst)
            {
                const Type omega = mk2::math::two_pi<Type> * freq / sample_rate;
                const Type cosw = std::cos(omega);
                const Type rcosw = 1 + cosw;
                const Type alpha = std::sin(omega) / (static_cast<Type>(2) * q);
                const Type A = std::pow (static_cast<Type>(10), dB * static_cast<Type>(0.025));
                const Type rA = A - 1;
                const Type fA = A + 1;
                const Type x = fA - rA * cosw;
                const Type y = fA + rA * cosw;
                const Type sa2 = 2 * std::sqrt(A) * alpha;

                dst[0] = A * (y + sa2);
                dst[1] = - 2 * A * (rA + fA * cosw);
                dst[2] = A * (y - sa2);
                dst[3] = x + sa2;
                dst[4] = 2 * (rA - fA * cosw);
                dst[5] = x - sa2;
            };
        }

        template <class Type>
        decltype(auto) band_pass(Type freq, Type bw)
        {
            return [freq, bw](Type sample_rate, Type* dst)
            {
                const Type omega = mk2::math::two_pi<Type> * freq / sample_rate;
                const Type cosw = std::cos(omega);
                const Type sinw = std::sin(omega);
                const Type alpha = sinw * std::sinh(std::log(static_cast<Type>(2)) / 2 * bw * omega / sinw);

                dst[0] = alpha;
                dst[1] = 0;
                dst[2] = -alpha;
                dst[3] = 1 + alpha;
                dst[4] = - 2 * cosw;
                dst[5] = 1 - alpha;
            };
        }

        template <class Type>
        decltype(auto) notch(Type freq, Type bw)
        {
            return [freq, bw](Type sample_rate, Type* dst)
            {
                const Type omega = mk2::math::two_pi<Type> * freq / sample_rate;
                const Type cosw = std::cos(omega);
                const Type sinw = std::sin(omega);
                const Type alpha = sinw * std::sinh(std::log(static_cast<Type>(2)) / 2 * bw * omega / sinw);

                dst[0] = 1;
                dst[1] = - 2 * cosw;
                dst[2] = 1;
                dst[3] = 1 + alpha;
                dst[4] = dst[1];
                dst[5] = 1 - alpha;
            };
        }

        template <class Type>
        decltype(auto) peak(Type freq, Type q, Type dB)
        {
            return [freq, q, dB](Type sample_rate, Type* dst)
            {
                const Type omega = mk2::math::two_pi<Type> * freq / sample_rate;
                const Type cosw = std::cos(omega);
                const Type rcosw = 1 + cosw;
                const Type alpha = std::sin(omega) / (static_cast<Type>(2) * q);
                const Type A = std::pow (static_cast<Type>(10), dB * static_cast<Type>(0.025));

                dst[0] = 1 + alpha * A;
                dst[1] = - 2 * cosw;
                dst[2] = 1 - alpha * A;
                dst[3] = 1 + alpha / A;
                dst[4] = dst[1];
                dst[5] = 1 - alpha / A;
            };
        }
    }
    
    template<class Type, int BiQuadOrder = 1>
    class bi_quad_filter
    {
        using ptr_type = std::unique_ptr<Ipp8u, mk2::simd::ipp::ipp_buffer_delete<Ipp8u>>;
        using state_type = mk2::simd::ipp::ipps_iir_state<Type>;
        
    public:
        explicit bi_quad_filter(Type sample_rate) : bi_quad_filter(sample_rate,
                bi_quad_coefficients::all_pass<Type>(static_cast<Type>(sample_rate / 2.f), mk2::math::inv_root_two<Type>))
        {}

        template <class Filter>
        bi_quad_filter(Type sample_rate, Filter&& f) : sample_rate_(sample_rate)
        {
            std::forward<Filter>(f)(sample_rate_, coefficients_.data());

            int buf_size;
            function::iir_get_state_size_bi_quad<Type>(BiQuadOrder, &buf_size);
            buffer_ = ptr_type(ippsMalloc_8u(buf_size));

            function::iir_init_bi_quad(&state_, coefficients_.data(), BiQuadOrder, static_cast<const Type*>(nullptr), buffer_.get());
        }
        
        void set_coefficients(const float* cofs)
        {
            function::copy(cofs, coefficients_.data(), BiQuadOrder * 6);
        }
    
        void operator()(const Type* src, Type* dst, int len)
        {
            function::iir(src, dst, len, state_);
        }
    
        void inplace(Type* src_dst, int len)
        {
            function::iir_inplace(src_dst, len, state_);
        }
        
    private:
        const Type sample_rate_;
        ptr_type buffer_;
        state_type *state_;
        std::array<Type, BiQuadOrder * 6> coefficients_;
        std::array<Type, BiQuadOrder * 2> delay_;
    };
}}}