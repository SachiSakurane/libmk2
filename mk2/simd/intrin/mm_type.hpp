//
// Created by Himatya on 2018-10-29.
//

#pragma once

#include <mk2/simd/intrin/include.hpp>

namespace mk2 { namespace simd { namespace intrin {

    struct m128{};
    struct m256{};
    struct m512{};

    template <class Type, class Register>
    struct mm_type {};

    template <>
    struct mm_type<float, m128>
    {
        size_t size = sizeof(__m128);
        typedef __m128 type;
    };

    template <>
    struct mm_type<float, m256>
    {
        size_t size = sizeof(__m256);
        typedef __m256 type;
    };

    template <>
    struct mm_type<float, m512>
    {
        size_t size = sizeof(__m512);
        typedef __m512 type;
    };

    template <>
    struct mm_type<double, m128>
    {
        size_t size = sizeof(__m128d);
        typedef __m128d type;
    };

    template <>
    struct mm_type<double, m256>
    {
        size_t size = sizeof(__m256d);
        typedef __m256d type;
    };

    template <>
    struct mm_type<double, m512>
    {
        size_t size = sizeof(__m512d);
        typedef __m512d type;
    };

    template <>
    struct mm_type<int, m128>
    {
        size_t size = sizeof(__m128i);
        typedef __m128i type;
    };

    template <>
    struct mm_type<int, m256>
    {
        size_t size = sizeof(__m256i);
        typedef __m256i type;
    };

    template <>
    struct mm_type<int, m512>
    {
        size_t size = sizeof(__m512i);
        typedef __m512i type;
    };
}}}