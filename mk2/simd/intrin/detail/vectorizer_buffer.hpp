//
// Created by Himatya on 2018-11-07.
//

#pragma once

#include <mk2/simd/intrin/function/arithmetic.hpp>
#include <mk2/simd/intrin/function/set.hpp>
#include <mk2/simd/intrin/type_traits/bit_type.hpp>

namespace mk2 { namespace simd { namespace intrin {

    template <class Type, class Bits, size_t Size, class Align> class vectorizer;

    namespace detail
    {
        // 一時バッファ的な役割
        // fmaに変換できるならしたい
        // lazyにすべき
        template <class Type, class Bits, size_t Size, class Align>
        struct vectorizer_buffer
        {
            using mm_type = typename mk2::simd::intrin::bit_type<Type, Bits>::type;
            static constexpr std::size_t mm_contain_size = sizeof(mm_type) / sizeof(Type);
            static constexpr std::size_t mm_elems_size = Size / mm_contain_size;

            mk2::simd::intrin::vectorizer<Type, Bits, Size, Align> to_vectorizer() const
            {
                return mk2::simd::intrin::vectorizer<Type, Bits, Size, Align>(container);
            }

            mm_type& operator[](size_t n) noexcept
            {
                return container[n];
            }

            mm_type container[mm_elems_size];
        };

#define MK2_INTRIN_VECTORIZER_BUFFER_ARITHMETIC_OPERATOR_TEMPLETE(op, op_name)          \
        template <class Type, class Bits, size_t Size, class Align>                     \
        inline vectorizer_buffer<Type, Bits, Size, Align> operator op(                  \
                vectorizer_buffer<Type, Bits, Size, Align>&& lhv,                       \
                vectorizer_buffer<Type, Bits, Size, Align>&& rhv)                       \
        {                                                                               \
            constexpr size_t size = vectorizer<Type, Bits, Size, Align>::mm_elems_size; \
            using mm_type = typename vectorizer<Type, Bits, Size, Align>::mm_type;      \
            for (std::size_t i = 0; i < size; i++)                                      \
            {                                                                           \
                lhv[i] = mk2::simd::intrin::function::op_name(lhv[i], rhv[i]);          \
            }                                                                           \
            return lhv;                                                                 \
        }                                                                               \
        template <class Type, class Bits, size_t Size, class Align>                     \
        inline vectorizer_buffer<Type, Bits, Size, Align> operator op(                  \
                const Type lhv,                                                         \
                vectorizer_buffer<Type, Bits, Size, Align>&& rhv)                       \
        {                                                                               \
            constexpr size_t size = vectorizer<Type, Bits, Size, Align>::mm_elems_size; \
            using mm_type = typename vectorizer<Type, Bits, Size, Align>::mm_type;      \
            decltype(auto) scalar = mk2::simd::intrin::function::set1<Bits>(lhv);       \
            for (std::size_t i = 0; i < size; i++)                                      \
            {                                                                           \
                rhv[i] = mk2::simd::intrin::function::op_name(scalar, rhv[i]);          \
            }                                                                           \
            return rhv;                                                                 \
        }                                                                               \
        template <class Type, class Bits, size_t Size, class Align>                     \
        inline vectorizer_buffer<Type, Bits, Size, Align> operator op(                  \
                vectorizer_buffer<Type, Bits, Size, Align>&& lhv,                       \
                const Type rhv)                                                         \
        {                                                                               \
            constexpr size_t size = vectorizer<Type, Bits, Size, Align>::mm_elems_size; \
            using mm_type = typename vectorizer<Type, Bits, Size, Align>::mm_type;      \
            decltype(auto) scalar = mk2::simd::intrin::function::set1<Bits>(rhv);       \
            for (std::size_t i = 0; i < size; i++)                                      \
            {                                                                           \
                lhv[i] = mk2::simd::intrin::function::op_name(lhv[i], scalar);          \
            }                                                                           \
            return lhv;                                                                 \
        }                                                                               \
        template <class Type, class Bits, size_t Size, class Align>                     \
        inline vectorizer_buffer<Type, Bits, Size, Align> operator op(                  \
                vectorizer_buffer<Type, Bits, Size, Align>&& lhv,                       \
                const vectorizer<Type, Bits, Size, Align>& rhv)                         \
        {                                                                               \
            constexpr size_t size = vectorizer<Type, Bits, Size, Align>::mm_elems_size; \
            using mm_type = typename vectorizer<Type, Bits, Size, Align>::mm_type;      \
            decltype(auto) mrhv = rhv.mm_data();                                        \
            detail::vectorizer_buffer<Type, Bits, Size, Align> container;               \
            for (std::size_t i = 0; i < size; i++)                                      \
            {                                                                           \
                lhv[i] = mk2::simd::intrin::function::op_name(lhv[i], mrhv[i]);         \
            }                                                                           \
            return lhv;                                                                 \
        }                                                                               \
        template <class Type, class Bits, size_t Size, class Align>                     \
        inline vectorizer_buffer<Type, Bits, Size, Align> operator op(                  \
                const vectorizer<Type, Bits, Size, Align>& lhv,                         \
                vectorizer_buffer<Type, Bits, Size, Align>&& rhv)                       \
        {                                                                               \
            constexpr size_t size = vectorizer<Type, Bits, Size, Align>::mm_elems_size; \
            using mm_type = typename vectorizer<Type, Bits, Size, Align>::mm_type;      \
            decltype(auto) mlhv = lhv.mm_data();                                        \
            detail::vectorizer_buffer<Type, Bits, Size, Align> container;               \
            for (std::size_t i = 0; i < size; i++)                                      \
            {                                                                           \
                rhv[i] = mk2::simd::intrin::function::op_name(mlhv[i], rhv[i]);         \
            }                                                                           \
            return rhv;                                                                 \
        }

        MK2_INTRIN_VECTORIZER_BUFFER_ARITHMETIC_OPERATOR_TEMPLETE(+, add)
        MK2_INTRIN_VECTORIZER_BUFFER_ARITHMETIC_OPERATOR_TEMPLETE(-, sub)
        MK2_INTRIN_VECTORIZER_BUFFER_ARITHMETIC_OPERATOR_TEMPLETE(*, mul)
        MK2_INTRIN_VECTORIZER_BUFFER_ARITHMETIC_OPERATOR_TEMPLETE(/, div)

#undef MK2_INTRIN_VECTORIZER_BUFFER_ARITHMETIC_OPERATOR_TEMPLETE
    }

    // arithmetic operator
    // 1024以下の場合に特化している
#define MK2_INTRIN_VECTORIZER_ARITHMETIC_OPERATOR_TEMPLETE(op, op_name)             \
    template <class Type, class Bits, size_t Size, class Align>                     \
    inline detail::vectorizer_buffer<Type, Bits, Size, Align> operator op(          \
            const vectorizer<Type, Bits, Size, Align>& lhv,                         \
            const vectorizer<Type, Bits, Size, Align>& rhv)                         \
    {                                                                               \
        constexpr size_t size = vectorizer<Type, Bits, Size, Align>::mm_elems_size; \
        decltype(auto) mlhv = lhv.mm_data();                                        \
        decltype(auto) mrhv = rhv.mm_data();                                        \
        using mm_type = typename vectorizer<Type, Bits, Size, Align>::mm_type;      \
        detail::vectorizer_buffer<Type, Bits, Size, Align> container;               \
        for (std::size_t i = 0; i < size; i++)                                      \
        {                                                                           \
            container[i] = mk2::simd::intrin::function::op_name(mlhv[i], mrhv[i]);  \
        }                                                                           \
        return container;                                                           \
    }                                                                               \
    template <class Type, class Bits, size_t Size, class Align>                     \
    inline detail::vectorizer_buffer<Type, Bits, Size, Align> operator op(          \
            const Type lhv,                                                         \
            const vectorizer<Type, Bits, Size, Align>& rhv)                         \
    {                                                                               \
        constexpr size_t size = vectorizer<Type, Bits, Size, Align>::mm_elems_size; \
        using mm_type = typename vectorizer<Type, Bits, Size, Align>::mm_type;      \
        decltype(auto) mlhv = mk2::simd::intrin::function::set1<Bits>(lhv);         \
        decltype(auto) mrhv = rhv.mm_data();                                        \
        detail::vectorizer_buffer<Type, Bits, Size, Align> container;               \
        for (std::size_t i = 0; i < size; i++)                                      \
        {                                                                           \
            container[i] = mk2::simd::intrin::function::op_name(mlhv, mrhv[i]);     \
        }                                                                           \
        return container;                                                           \
    }                                                                               \
    template <class Type, class Bits, size_t Size, class Align>                     \
    inline detail::vectorizer_buffer<Type, Bits, Size, Align> operator op(          \
            const vectorizer<Type, Bits, Size, Align>& lhv,                         \
            const Type rhv)                                                         \
    {                                                                               \
        constexpr size_t size = vectorizer<Type, Bits, Size, Align>::mm_elems_size; \
        using mm_type = typename vectorizer<Type, Bits, Size, Align>::mm_type;      \
        decltype(auto) mlhv = lhv.mm_data();                                        \
        decltype(auto) mrhv = mk2::simd::intrin::function::set1<Bits>(rhv);         \
        detail::vectorizer_buffer<Type, Bits, Size, Align> container;               \
        for (std::size_t i = 0; i < size; i++)                                      \
        {                                                                           \
            container[i] = mk2::simd::intrin::function::op_name(mlhv[i], mrhv);     \
        }                                                                           \
        return container;                                                           \
    }

    MK2_INTRIN_VECTORIZER_ARITHMETIC_OPERATOR_TEMPLETE(+, add)
    MK2_INTRIN_VECTORIZER_ARITHMETIC_OPERATOR_TEMPLETE(-, sub)
    MK2_INTRIN_VECTORIZER_ARITHMETIC_OPERATOR_TEMPLETE(*, mul)
    MK2_INTRIN_VECTORIZER_ARITHMETIC_OPERATOR_TEMPLETE(/, div)

#undef MK2_INTRIN_VECTORIZER_ARITHMETIC_OPERATOR_TEMPLETE

}}}
