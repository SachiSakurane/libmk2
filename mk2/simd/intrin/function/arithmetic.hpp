//
// Created by Himatya on 2018-11-02.
//

#pragma once

#include <mk2/simd/intrin/type_traits/architecture.hpp>
#include <mk2/simd/intrin/wrapper/intel/arithmetic.hpp>

namespace mk2 { namespace simd { namespace intrin { namespace function {

    namespace detail
    {
        template <class Type>
        struct add
        {
            static decltype(auto) func(Type a, Type b, mk2::simd::intrin::arch_sse)
            {
                return mk2::simd::intrin::wrapper::intel::add(a, b);
            }
        };

        template <class Type>
        struct sub
        {
            static decltype(auto) func(Type a, Type b, mk2::simd::intrin::arch_sse)
            {
                return mk2::simd::intrin::wrapper::intel::sub(a, b);
            }
        };

        template <class Type>
        struct mul
        {
            static decltype(auto) func(Type a, Type b, mk2::simd::intrin::arch_sse)
            {
                return mk2::simd::intrin::wrapper::intel::mul(a, b);
            }
        };

        template <class Type>
        struct div
        {
            static decltype(auto) func(Type a, Type b, mk2::simd::intrin::arch_sse)
            {
                return mk2::simd::intrin::wrapper::intel::div(a, b);
            }
        };
    }

    template <class Type>
    inline decltype(auto) add(Type a, Type b)
    {
        return detail::add<Type>::func(a, b, mk2::simd::intrin::available_architecture);
    }

    template <class Type>
    inline decltype(auto) sub(Type a, Type b)
    {
        return detail::sub<Type>::func(a, b, mk2::simd::intrin::available_architecture);
    }

    template <class Type>
    inline decltype(auto) mul(Type a, Type b)
    {
        return detail::mul<Type>::func(a, b, mk2::simd::intrin::available_architecture);
    }

    template <class Type>
    inline decltype(auto) div(Type a, Type b)
    {
        return detail::div<Type>::func(a, b, mk2::simd::intrin::available_architecture);
    }

}}}}