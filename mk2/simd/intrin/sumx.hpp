//
// Created by Himatya on 2018-10-28.
//

#pragma once

#include <mk2/simd/intrin/include.hpp>

namespace mk2 { namespace simd { namespace intrin {

    namespace detail
    {
        // require的なヤツで対応命令でコンパイル時分岐できそう

        // fold
        inline float mm_sum_ps(const __m128 x)
        {
            const __m128 loDual = x;
            const __m128 hiDual = _mm_shuffle_ps(x, x, _MM_SHUFFLE(1, 0, 3, 2));
            const __m128 sumDual = _mm_add_ps(loDual, hiDual);

            const __m128 lo = sumDual;
            const __m128 hi = _mm_shuffle_ps(sumDual, sumDual, _MM_SHUFFLE(2, 1, 0, 3));
            return _mm_add_ss(lo, hi)[0];
        }

        inline float mm256_sum_ps(const __m256 x)
        {
            const __m128 hiQuad = _mm256_extractf128_ps(x, 1);
            const __m128 loQuad = _mm256_castps256_ps128(x);

            return mm_sum_ps(_mm_add_ps(loQuad, hiQuad));
        }

        inline double mm_sum_pd(const __m128d x)
        {
            const __m128d lo = x;
            const __m128d hi = _mm_shuffle_pd(x, x, _MM_SHUFFLE2(0, 1));

            return _mm_add_sd(lo, hi)[0];
        }

        inline double mm256_sum_pd(const __m256d x)
        {
            const __m128d hiDual = _mm256_extractf128_pd(x, _MM_SHUFFLE2(0, 1));
            const __m128d loDual = _mm256_castpd256_pd128(x);
            const __m128d sumDual = _mm_add_pd(loDual, hiDual);

            return mm_sum_pd(_mm_add_pd(loDual, hiDual));
        }

        // vector sum xn
        inline __m256 mm256x8_sum_ps(const float* ary)
        {
            constexpr size_t unit = sizeof(__m256) / sizeof(float);

            const __m256 m0 = _mm256_load_ps(ary);
            const __m256 m1 = _mm256_load_ps(ary + unit);
            const __m256 m2 = _mm256_load_ps(ary + unit * 2);
            const __m256 m3 = _mm256_load_ps(ary + unit * 3);
            const __m256 m4 = _mm256_load_ps(ary + unit * 4);
            const __m256 m5 = _mm256_load_ps(ary + unit * 5);
            const __m256 m6 = _mm256_load_ps(ary + unit * 6);
            const __m256 m7 = _mm256_load_ps(ary + unit * 7);

            return _mm256_add_ps(
                    _mm256_add_ps(_mm256_add_ps(m0, m1), _mm256_add_ps(m2, m3)),
                    _mm256_add_ps(_mm256_add_ps(m4, m5), _mm256_add_ps(m6, m7)));
        }

        inline __m256 mm256x4_sum_ps(const float* ary)
        {
            constexpr size_t unit = sizeof(__m256) / sizeof(float);

            const __m256 m0 = _mm256_load_ps(ary);
            const __m256 m1 = _mm256_load_ps(ary + unit);
            const __m256 m2 = _mm256_load_ps(ary + unit * 2);
            const __m256 m3 = _mm256_load_ps(ary + unit * 3);

            return _mm256_add_ps(_mm256_add_ps(m0, m1), _mm256_add_ps(m2, m3));
        }

        inline __m256 mm256x2_sum_ps(const float* ary)
        {
            constexpr size_t unit = sizeof(__m256) / sizeof(float);

            const __m256 m0 = _mm256_load_ps(ary);
            const __m256 m1 = _mm256_load_ps(ary + unit);

            return _mm256_add_ps(m0, m1);
        }

        inline __m256d mm256x4_sum_pd(const double* ary)
        {
            constexpr size_t unit = sizeof(__m256d) / sizeof(double);

            const __m256d m0 = _mm256_load_pd(ary + 0);
            const __m256d m1 = _mm256_load_pd(ary + unit);
            const __m256d m2 = _mm256_load_pd(ary + unit * 2);
            const __m256d m3 = _mm256_load_pd(ary + unit * 3);

            return _mm256_add_pd(_mm256_add_pd(m0, m1), _mm256_add_pd(m2, m3));
        }

        inline __m256d mm256x2_sum_pd(const double* ary)
        {
            constexpr size_t unit = sizeof(__m256d) / sizeof(double);

            const __m256d m0 = _mm256_load_pd(ary);
            const __m256d m1 = _mm256_load_pd(ary + unit);

            return _mm256_add_pd(m0, m1);
        }

        // impl
        template <class Type, size_t Size>
        struct sum_impl{};

        template <size_t Size>
        struct sum_impl<float, Size>
        {
            static float func (const float* ary)
            {
                constexpr size_t unit = sizeof(__m256) / sizeof(float);

                constexpr size_t x8size = (Size / (unit * 8)) * unit * 8;
                constexpr size_t x4size = ((Size - x8size) / (unit * 4)) * unit * 4;
                constexpr size_t x2size = ((Size - x8size - x4size) / (unit * 2)) * unit * 2;

                __m256 msum = _mm256_setzero_ps();

                if constexpr (Size >= unit * 8)
                {
                    constexpr size_t interval = 8 * unit;

                    for (size_t i = 0; i < x8size; i += interval)
                    {
                        msum = _mm256_add_ps(msum, mm256x8_sum_ps(ary + i));
                    }
                }

                if constexpr ((Size - x8size) >= unit * 4)
                {
                    msum = _mm256_add_ps(msum, mm256x4_sum_ps(ary + x8size));
                }

                if constexpr ((Size - x8size - x4size) >= unit * 2)
                {
                    msum = _mm256_add_ps(msum, mm256x2_sum_ps(ary + x8size + x4size));
                }

                if constexpr ((Size - x8size - x4size - x2size) >= unit)
                {
                    msum = _mm256_add_ps(msum, _mm256_load_ps(ary + x8size + x4size + x2size));
                }

                return mm256_sum_ps(msum);
            }
        };

        template <size_t Size>
        struct sum_impl<double, Size>
        {
            static double func (const double* ary)
            {
                constexpr size_t unit = sizeof(__m256d) / sizeof(double);

                constexpr size_t x4size = ((Size) / (unit * 4)) * unit * 4;
                constexpr size_t x2size = ((Size - x4size) / (unit * 2)) * unit * 2;

                __m256d msum = _mm256_setzero_pd();

                if constexpr (Size >= unit * 4)
                {
                    constexpr size_t interval = 4 * unit;

                    for (size_t i = 0; i < x4size; i += interval)
                    {
                        msum = _mm256_add_pd(msum, mm256x4_sum_pd(ary + i));
                    }
                }

                if constexpr ((Size - x4size) >= unit * 2)
                {
                    msum = _mm256_add_pd(msum, mm256x2_sum_pd(ary + x4size));
                }

                if constexpr ((Size - x4size - x2size) >= unit)
                {
                    msum = _mm256_add_pd(msum, _mm256_load_pd(ary + x4size + x2size));
                }

                return mm256_sum_pd(msum);
            }
        };
    }

    template <class Type, size_t Size>
    inline Type sum (const Type* ary)
    {
        return detail::sum_impl<Type, Size>::func(ary);
    }

}}}