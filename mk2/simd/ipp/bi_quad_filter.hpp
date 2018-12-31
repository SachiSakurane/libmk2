//
// Created by Himatya on 2018/08/14.
//

#pragma once

#include <array>
#include <cmath>

#include <mk2/container/fixed_array.hpp>
#include <mk2/math/constants.hpp>
#include <mk2/simd/ipp/type.hpp>
#include <mk2/simd/ipp/function/filtering.hpp>

// 双二次フィルタ

namespace mk2 { namespace simd { namespace ipp {

    // sample rate, freq, q -> lambda(dst)を返すような感じ？
    namespace bi_quad_coefficients
    {
        namespace detail
        {

        }

        template <class Type>
        decltype(auto) all_pass(Type sample_rate, Type freq, Type q)
        {
            return [sample_rate, freq, q](Type* dst)
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
        decltype(auto) low_pass(Type sample_rate, Type freq, Type q)
        {
            return [sample_rate, freq, q](Type* dst)
            {
                const Type omega = mk2::math::two_pi<Type> * freq / sample_rate;
                const Type cosw = std::cos(omega);
                const Type rcosw = 1 - cosw;
                const Type alpha = std::sin(omega) / (static_cast<Type>(2) * q);

                dst[0] = 1 + alpha;
                dst[1] = - 2 * cosw;
                dst[2] = 1 - alpha;
                dst[3] = rcosw / 2;
                dst[4] = rcosw;
                dst[5] = dst[3];
            };
        }

        template <class Type>
        decltype(auto) high_pass(Type sample_rate, Type freq, Type q)
        {
            return [sample_rate, freq, q](Type* dst)
            {
                const Type omega = mk2::math::two_pi<Type> * freq / sample_rate;
                const Type cosw = std::cos(omega);
                const Type rcosw = 1 + cosw;
                const Type alpha = std::sin(omega) / (static_cast<Type>(2) * q);

                dst[0] = 1 + alpha;
                dst[1] = - 2 * cosw;
                dst[2] = 1 - alpha;
                dst[3] = rcosw / 2;
                dst[4] = -rcosw;
                dst[5] = dst[3];
            };
        }

        template <class Type>
        decltype(auto) low_shelf(Type sample_rate, Type freq, Type q, Type dB)
        {
            return [sample_rate, freq, q, dB](Type* dst)
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

                dst[0] = x + sa2;
                dst[1] = - 2 * (rA + fA * cosw);
                dst[2] = x - sa2;
                dst[3] = A * (y + sa2);
                dst[4] = 2 * A * (rA - fA * cosw);
                dst[5] = A * (y - sa2);
            };
        }

        template <class Type>
        decltype(auto) high_shelf(Type sample_rate, Type freq, Type q, Type dB)
        {
            return [sample_rate, freq, q, dB](Type* dst)
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

                dst[0] = x + sa2;
                dst[1] = 2 * (rA - fA * cosw);
                dst[2] = x - sa2;
                dst[3] = A * (y + sa2);
                dst[4] = - 2 * A * (rA + fA * cosw);
                dst[5] = A * (y - sa2);
            };
        }

        template <class Type>
        decltype(auto) band_pass(Type sample_rate, Type freq, Type bw)
        {
            return [sample_rate, freq, bw](Type* dst)
            {
                const Type omega = mk2::math::two_pi<Type> * freq / sample_rate;
                const Type cosw = std::cos(omega);
                const Type sinw = std::sin(omega);
                const Type alpha = sinw * std::sinh(std::log(static_cast<Type>(2)) / 2 * bw * omega / sinw);

                dst[0] = 1 + alpha;
                dst[1] = - 2 * cosw;
                dst[2] = 1 - alpha;
                dst[3] = alpha;
                dst[4] = 0;
                dst[5] = -alpha;
            };
        }

        template <class Type>
        decltype(auto) notch(Type sample_rate, Type freq, Type bw)
        {
            return [sample_rate, freq, bw](Type* dst)
            {
                const Type omega = mk2::math::two_pi<Type> * freq / sample_rate;
                const Type cosw = std::cos(omega);
                const Type sinw = std::sin(omega);
                const Type alpha = sinw * std::sinh(std::log(static_cast<Type>(2)) / 2 * bw * omega / sinw);

                dst[0] = 1 + alpha;
                dst[1] = - 2 * cosw;
                dst[2] = 1 - alpha;
                dst[3] = 1;
                dst[4] = dst[1];
                dst[5] = 1;
            };
        }

        template <class Type>
        decltype(auto) peak(Type sample_rate, Type freq, Type q, Type dB)
        {
            return [sample_rate, freq, q, dB](Type* dst)
            {
                const Type omega = mk2::math::two_pi<Type> * freq / sample_rate;
                const Type cosw = std::cos(omega);
                const Type rcosw = 1 + cosw;
                const Type alpha = std::sin(omega) / (static_cast<Type>(2) * q);
                const Type A = std::pow (static_cast<Type>(10), dB * static_cast<Type>(0.025));

                dst[0] = 1 + alpha / A;
                dst[1] = - 2 * cosw;
                dst[2] = 1 - alpha / A;
                dst[3] = 1 + alpha * A;
                dst[4] = dst[1];
                dst[5] = 1 - alpha * A;
            };
        }
    }
    
    template<class Type, int BiQuadOrder = 1>
    class bi_quad_filter
    {
        using state_type = mk2::simd::ipp::ipps_iir_state<Type>;
        
    public:
        bi_quad_filter(Type sample_rate) : bi_quad_filter(sample_rate,
                bi_quad_coefficients::all_pass<Type>(sample_rate, static_cast<Type>(100), mk2::math::inv_root_two<Type>)) {}

        template <class Filter>
        bi_quad_filter(Type sample_rate, Filter&& f) : sample_rate_(sample_rate)
        {
            int buf_size;
            function::iir_get_state_size_bi_quad<Type>(BiQuadOrder, &buf_size);
            buffer_ = ippsMalloc_8u(buf_size);
            std::forward<Filter>(f)(coefficients_.data());
            function::iir_init_bi_quad(&state, coefficients_.data(), BiQuadOrder, static_cast<const Type*>(nullptr), buffer_);

        }

        ~bi_quad_filter()
        {
            if (buffer_)
                ippsFree(buffer_);
        }
        
        void set_coefficients(const float* cofs)
        {
            function::copy(cofs, coefficients_.data(), BiQuadOrder * 6);
        }
    
        void operator()(const Type* src, Type* dst, int len)
        {
            function::iir(src, dst, len, state);
        }
    
        void inplace(Type* src_dst, int len)
        {
            function::iir_inplace(src_dst, len, state);
        }
        
    private:
        const Type sample_rate_;
        Ipp8u *buffer_;
        state_type *state;
        std::array<Type, BiQuadOrder * 6> coefficients_;
        std::array<Type, BiQuadOrder * 2> delay_;
    };
}}}