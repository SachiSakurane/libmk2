//
// Created by Himatya on 2018-11-04.
//

#pragma once

#include <mk2/simd/intrin/type_traits/architecture.hpp>
#include <mk2/simd/intrin/type_traits/alignment.hpp>
#include <mk2/simd/intrin/wrapper/intel/assignment.hpp>

namespace mk2 { namespace simd { namespace intrin { namespace function {

    namespace detail
    {
        template <class Bit, class Type, class Align>
        struct load
        {
            static decltype(auto) func(const Type* mem_addr, mk2::simd::intrin::arch_sse)
            {
                return mk2::simd::intrin::wrapper::intel::load<Bit, Type, Align>(mem_addr);
            }
        };

        template <class Bit, class Type, class Align>
        struct store
        {
            static decltype(auto) func(Type* mem_addr, typename bit_type<Type, Bit>::type r, mk2::simd::intrin::arch_sse)
            {
                return mk2::simd::intrin::wrapper::intel::store<Bit, Type, Align>(mem_addr, r);
            }
        };

        template <class Bit, class Type, class Align>
        struct stream
        {
            static decltype(auto) func(Type* mem_addr, typename bit_type<Type, Bit>::type r, mk2::simd::intrin::arch_sse)
            {
                return mk2::simd::intrin::wrapper::intel::stream<Bit, Type, Align>(mem_addr, r);
            }
        };
    }

    template <class Bit, class Type, class Align = mk2::simd::intrin::aligned>
    inline decltype(auto) load(const Type* mem_addr)
    {
        return detail::load<Bit, Type, Align>::func(mem_addr, mk2::simd::intrin::available_architecture);
    }

    template <class Bit, class Type, class Align = mk2::simd::intrin::aligned>
    inline decltype(auto) store(Type* mem_addr, typename bit_type<Type, Bit>::type r)
    {
        return detail::store<Bit, Type, Align>::func(mem_addr, r, mk2::simd::intrin::available_architecture);
    }

    template <class Bit, class Type, class Align = mk2::simd::intrin::aligned>
    inline decltype(auto) stream(Type* mem_addr, typename bit_type<Type, Bit>::type r)
    {
        return detail::stream<Bit, Type, Align>::func(mem_addr, r, mk2::simd::intrin::available_architecture);
    }

}}}}