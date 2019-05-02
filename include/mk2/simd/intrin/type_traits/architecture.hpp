//
// Created by Himatya on 2018-11-04.
//

#pragma once

#include <type_traits>

#include <mk2/utility/overload_priority.hpp>

// 継承元1つにしないと推論が曖昧になってしまう

namespace mk2 { namespace simd { namespace intrin {

    namespace detail
    {
        template <class Type>
        struct un_available {};

        template <class Type>
        struct is_available : std::conditional<Type::value, Type, un_available<Type>>::type {};

        template <class Type, class... Args>
        struct available_architecture_impl : std::conditional<Type::value, Type, available_architecture_impl<Args...>>::type {};

        template <class Type>
        struct available_architecture_impl<Type> : is_available<Type> {};
    }

    struct arch_mmx
    {
#ifdef __MMX__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_sse : arch_mmx
    {
#ifdef __SSE__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_sse2 : arch_sse
    {
#ifdef __SSE2__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_sse3 : arch_sse2
    {
#ifdef __SSE3__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_ssse3 : arch_sse3
    {
#ifdef __SSSE3__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_sse4_1 : arch_ssse3
    {
#ifdef __SSE4_1__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_sse4_2 : arch_sse4_1
    {
#ifdef __SSE4_2__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_avx : arch_sse4_2
    {
#ifdef __AVX__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_avx2 : arch_avx
    {
#ifdef __AVX2__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_fma : arch_avx2
    {
#ifdef __FMA__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_avx512vbmi
    {
#ifdef __AVX512VBMI__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_avx512ifma
    {
#ifdef __AVX512IFMA__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_avx512vl
    {
#ifdef __AVX512VL__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_avx512bw
    {
#ifdef __AVX512BW__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_avx512dq
    {
#ifdef __AVX512DQ__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_avx512pf
    {
#ifdef __AVX512PF__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_avx512cd
    {
#ifdef __AVX512CD__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_avx512er
    {
#ifdef __AVX512ER__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_avx512f
    {
#ifdef __AVX512F__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_arm_neon
    {
#ifdef __ARM_NEON__
        static constexpr bool value = true;
#else
        static constexpr bool value = false;
#endif
    };

    struct arch_avx512
            : arch_fma,
              detail::is_available<arch_avx512f>,
              detail::is_available<arch_avx512er>,
              detail::is_available<arch_avx512cd>,
              detail::is_available<arch_avx512pf>,
              detail::is_available<arch_avx512dq>,
              detail::is_available<arch_avx512bw>,
              detail::is_available<arch_avx512vl>,
              detail::is_available<arch_avx512ifma>,
              detail::is_available<arch_avx512vbmi> {};

    struct available_architecture_t
            : detail::available_architecture_impl<
                    arch_avx512,
                    arch_fma,
                    arch_avx2,
                    arch_avx,
                    arch_sse4_2,
                    arch_sse4_1,
                    arch_ssse3,
                    arch_sse3,
                    arch_sse2,
                    arch_sse,
                    arch_mmx,
                    arch_arm_neon
            > {};

    static constexpr const available_architecture_t available_architecture;

}}}