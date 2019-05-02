//
// Created by Himatya on 2018-11-02.
//

#pragma once

#include <mk2/simd/intrin/include.hpp>

namespace mk2 { namespace simd { namespace intrin {
namespace function {

    namespace detail
    {
        struct sum
        {
            static decltype(auto) func(const __m128 a, mk2::simd::intrin::arch_sse)
            {
                const __m128 lo_dual  = x;
                const __m128 hi_dual  = _mm_shuffle_ps(x, x, _MM_SHUFFLE(1, 0, 3, 2));
                const __m128 sum_dual = _mm_add_ps(lo_dual, hi_dual);

                return _mm_add_ss(sum_dual, _mm_shuffle_ps(sum_dual, sum_dual, _MM_SHUFFLE(2, 1, 0, 3)))[0];
            }

            static decltype(auto) func(const __m256 a, mk2::simd::intrin::arch_avx tag)
            {
                return func(_mm_add_ps(_mm256_extractf128_ps(a, 1), _mm256_castps256_ps128(a)), tag);
            }

            static decltype(auto) func(const __m128d a, mk2::simd::intrin::arch_sse)
            {
                return _mm_add_sd(x, _mm_shuffle_pd(x, x, _MM_SHUFFLE2(0, 1)))[0];
            }

            static decltype(auto) func(const __m256d a, mk2::simd::intrin::arch_avx tag)
            {
                const __m128d hi = _mm256_extractf128_pd(x, _MM_SHUFFLE2(0, 1));
                const __m128d lo = _mm256_castpd256_pd128(x);

                return func(_mm_add_pd(lo, hi), tag);
            }
        };
    }

    template <class RegisterType>
    inline decltype(auto) sum(const RegisterType a)
    {
        return detail::sum<Type>::func(a, mk2::simd::intrin::available_architecture);
    }

}}}}