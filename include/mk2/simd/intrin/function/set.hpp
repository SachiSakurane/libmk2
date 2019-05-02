//
// Created by Himatya on 2018-11-04.
//

#pragma once

#include <mk2/simd/intrin/type_traits/architecture.hpp>
#include <mk2/simd/intrin/type_traits/alignment.hpp>
#include <mk2/simd/intrin/wrapper/intel/set.hpp>

namespace mk2 { namespace simd { namespace intrin { namespace function {

    namespace detail
    {
        template <class Bit, class Type>
        struct setzero
        {
            static decltype(auto) func(mk2::simd::intrin::arch_sse)
            {
                return mk2::simd::intrin::wrapper::intel::setzero<Bit, Type>();
            }
        };

        template <class Bit, class Type>
        struct set1
        {
            static decltype(auto) func(Type a, mk2::simd::intrin::arch_sse)
            {
                return mk2::simd::intrin::wrapper::intel::set1<Bit, Type>(a);
            }
        };
    }

    template <class Bit, class Type>
    inline decltype(auto) setzero()
    {
        return detail::setzero<Bit, Type>::func(mk2::simd::intrin::available_architecture);
    }

    template <class Bit, class Type>
    inline decltype(auto) set1(Type a)
    {
        return detail::set1<Bit, Type>::func(a, mk2::simd::intrin::available_architecture);
    }

}}}}