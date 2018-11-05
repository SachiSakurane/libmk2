//
// Created by Himatya on 2018-11-04.
//

#pragma once

#include <mk2/simd/intrin/type_traits/architecture.hpp>
#include <mk2/simd/intrin/wrapper/intel/logical.hpp>

namespace mk2 { namespace simd { namespace intrin {
namespace function {

    namespace detail
    {
        template <class Type>
        struct bit_and
        {
            static decltype(auto) func(Type a, Type b, mk2::simd::intrin::arch_sse)
            {
                return mk2::simd::intrin::wrapper::intel::bit_and(a, b);
            }
        };

        template <class Type>
        struct bit_andnot
        {
            static decltype(auto) func(Type a, Type b, mk2::simd::intrin::arch_sse)
            {
                return mk2::simd::intrin::wrapper::intel::bit_andnot(a, b);
            }
        };

        template <class Type>
        struct bit_or
        {
            static decltype(auto) func(Type a, Type b, mk2::simd::intrin::arch_sse)
            {
                return mk2::simd::intrin::wrapper::intel::bit_or(a, b);
            }
        };

        template <class Type>
        struct bit_xor
        {
            static decltype(auto) func(Type a, Type b, mk2::simd::intrin::arch_sse)
            {
                return mk2::simd::intrin::wrapper::intel::bit_xor(a, b);
            }
        };

        template <class Type>
        struct testc
        {
            static decltype(auto) func(Type a, Type b, mk2::simd::intrin::arch_sse)
            {
                return mk2::simd::intrin::wrapper::intel::testc(a, b);
            }

            [[deprecated("float only")]]
            static decltype(auto) func(Type a, Type b, mk2::simd::intrin::arch_avx512)
            {
                const auto a_lo = _mm512_castps512_ps256(a);
                const auto b_lo = _mm512_castps512_ps256(b);
                const auto a_hi = _mm512_extractf32x8_ps(a, _MM_SHUFFLE2(0, 1));
                const auto b_hi = _mm512_extractf32x8_ps(b, _MM_SHUFFLE2(0, 1));
                return mk2::simd::intrin::wrapper::intel::testc(a_hi, b_hi) |
                       mk2::simd::intrin::wrapper::intel::testc(a_lo, b_lo);
            }
        };

        template <class Type>
        struct testz
        {
            static decltype(auto) func(Type a, Type b, mk2::simd::intrin::arch_sse)
            {
                return mk2::simd::intrin::wrapper::intel::testz(a, b);
            }

            [[deprecated("float only")]]
            static decltype(auto) func(Type a, Type b, mk2::simd::intrin::arch_avx512)
            {
                const auto a_lo = _mm512_castps512_ps256(a);
                const auto b_lo = _mm512_castps512_ps256(b);
                const auto a_hi = _mm512_extractf32x8_ps(a, _MM_SHUFFLE2(0, 1));
                const auto b_hi = _mm512_extractf32x8_ps(b, _MM_SHUFFLE2(0, 1));
                return mk2::simd::intrin::wrapper::intel::testz(a_hi, b_hi) |
                       mk2::simd::intrin::wrapper::intel::testz(a_lo, b_lo);
            }
        };
    }

    template <class Type>
    inline decltype(auto) bit_and(Type a, Type b)
    {
        return detail::bit_and<Type>::func(a, b, mk2::simd::intrin::available_architecture);
    }

    template <class Type>
    inline decltype(auto) bit_andnot(Type a, Type b)
    {
        return detail::bit_andnot<Type>::func(a, b, mk2::simd::intrin::available_architecture);
    }

    template <class Type>
    inline decltype(auto) bit_or(Type a, Type b)
    {
        return detail::bit_or<Type>::func(a, b, mk2::simd::intrin::available_architecture);
    }

    template <class Type>
    inline decltype(auto) bit_xor(Type a, Type b)
    {
        return detail::bit_xor<Type>::func(a, b, mk2::simd::intrin::available_architecture);
    }

    template <class Type>
    inline decltype(auto) testc(Type a, Type b)
    {
        return detail::testc<Type>::func(a, b, mk2::simd::intrin::available_architecture);
    }

    template <class Type>
    inline decltype(auto) testz(Type a, Type b)
    {
        return detail::testz<Type>::func(a, b, mk2::simd::intrin::available_architecture);
    }

}}}}