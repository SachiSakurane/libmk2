//
// Created by Himatya on 2018-11-02.
//

#pragma once

#include <mk2/simd/intrin/type_traits/architecture.hpp>
#include <mk2/simd/intrin/wrapper/intel/arithmetic.hpp>

namespace mk2 { namespace simd { namespace intrin { namespace function {

#define MK2_ARITHMETIC_FUNCTION_TEMPLETE(name)                                              \
    namespace detail                                                                        \
    {                                                                                       \
        template <class Type> struct name                                                   \
        {                                                                                   \
            static decltype(auto) func(Type a, Type b, mk2::simd::intrin::arch_sse)         \
            {                                                                               \
                return mk2::simd::intrin::wrapper::intel::name(a, b);                       \
            }                                                                               \
        };                                                                                  \
    }                                                                                       \
    template <class Type> inline decltype(auto) name(Type a, Type b)                        \
    {                                                                                       \
        return detail::name<Type>::func(a, b, mk2::simd::intrin::available_architecture);   \
    }

    MK2_ARITHMETIC_FUNCTION_TEMPLETE(add)
    MK2_ARITHMETIC_FUNCTION_TEMPLETE(sub)
    MK2_ARITHMETIC_FUNCTION_TEMPLETE(div)
    MK2_ARITHMETIC_FUNCTION_TEMPLETE(mul)

#undef MK2_ARITHMETIC_FUNCTION_TEMPLETE

#define MK2_ARITHMETIC_AVX_FUNCTION_TEMPLETE(name)                                          \
    namespace detail                                                                        \
    {                                                                                       \
        template <class Type> struct name                                                   \
        {                                                                                   \
            static decltype(auto) func(Type a, Type b, Type c, mk2::simd::intrin::arch_fma) \
            {                                                                               \
                return mk2::simd::intrin::wrapper::intel::name(a, b, c);                    \
            }                                                                               \
        };                                                                                  \
    }                                                                                       \
    template <class Type> inline decltype(auto) name(Type a, Type b, Type c)                \
    {                                                                                       \
        return detail::name<Type>::func(a, b, c, mk2::simd::intrin::available_architecture);\
    }

    MK2_ARITHMETIC_AVX_FUNCTION_TEMPLETE(fmadd)
    MK2_ARITHMETIC_AVX_FUNCTION_TEMPLETE(fmsub)
    MK2_ARITHMETIC_AVX_FUNCTION_TEMPLETE(fnmadd)
    MK2_ARITHMETIC_AVX_FUNCTION_TEMPLETE(fnmsub)
    MK2_ARITHMETIC_AVX_FUNCTION_TEMPLETE(fmaddsub)
    MK2_ARITHMETIC_AVX_FUNCTION_TEMPLETE(fmsubadd)

#undef MK2_ARITHMETIC_AVX_FUNCTION_TEMPLETE

}}}}