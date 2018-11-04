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
        template <class RegisterType>
        struct setzero
        {
            static decltype(auto) func(mk2::simd::intrin::arch_sse)
            {
                return mk2::simd::intrin::wrapper::intel::setzero<RegisterType>();
            }
        };

        template <class Type, class RegisterType>
        struct set1
        {
            static decltype(auto) func(Type a, mk2::simd::intrin::arch_sse)
            {
                return mk2::simd::intrin::wrapper::intel::set1<Type, RegisterType>(a);
            }
        };
    }

    template <class RegisterType>
    inline decltype(auto) setzero()
    {
        return detail::setzero<RegisterType>::func(mk2::simd::intrin::available_architecture);
    }

    template <class Type, class RegisterType>
    inline decltype(auto) set1(Type a)
    {
        return detail::set1<Type, RegisterType>::func(a, mk2::simd::intrin::available_architecture);
    }

}}}}