//
// Created by Himatya on 2018-11-07.
//

#pragma once

#include <cstddef>

#include <mk2/simd/intrin/vectorizer.hpp>
#include <mk2/simd/intrin/function/arithmetic.hpp>
#include <mk2/simd/intrin/function/set.hpp>
#include <mk2/simd/intrin/type_traits/bit_type.hpp>

namespace mk2 { namespace simd { namespace intrin
{
	
    template <class Bits, class Type, std::size_t Size> class vectorizer;

    namespace detail
    {
        // 演算子の一時バッファとして扱うことでバッファ生成を最小化する
        // fmaに変換できるならしたい
        // lazy化したい
        template <class Bits, class Type, std::size_t Size>
        struct vectorizer_buffer
        {
            using mm_type = typename mk2::simd::intrin::bit_type<Type, Bits>::type;
            static constexpr std::size_t mm_contain_size = sizeof(mm_type) / sizeof(Type);
            static constexpr std::size_t mm_elems_size = Size / mm_contain_size;

            mk2::simd::intrin::vectorizer<Bits, Type, Size> to_vectorizer() const
            {
                return mk2::simd::intrin::vectorizer<Bits, Type, Size>(container);
            }

            mm_type& operator[](std::size_t n) noexcept
            {
                return container[n];
            }

            mm_type container[mm_elems_size];
        };

        
#define MK2_INTRIN_VECTORIZER_BUFFER_ARITHMETIC_OPERATOR_TEMPLETE(op, op_name)          \
        template <class Bits, class Type, std::size_t Size>                             \
        inline vectorizer_buffer<Bits, Type, Size> operator op(                         \
                vectorizer_buffer<Bits, Type, Size>&& lhv,                              \
                vectorizer_buffer<Bits, Type, Size>&& rhv)                              \
        {                                                                               \
            constexpr std::size_t size = vectorizer<Bits, Type, Size>::mm_elems_size;   \
            for (std::size_t i = 0; i < size; i++)                                      \
            {                                                                           \
                lhv[i] = mk2::simd::intrin::function::op_name(lhv[i], rhv[i]);          \
            }                                                                           \
            return lhv;                                                                 \
        }                                                                               \
        template <class Bits, class Type, std::size_t Size>                             \
        inline vectorizer_buffer<Bits, Type, Size> operator op(                         \
                const Type lhv,                                                         \
                vectorizer_buffer<Bits, Type, Size>&& rhv)                              \
        {                                                                               \
            constexpr std::size_t size = vectorizer<Bits, Type, Size>::mm_elems_size;   \
            decltype(auto) scalar = mk2::simd::intrin::function::set1<Bits>(lhv);       \
            for (std::size_t i = 0; i < size; i++)                                      \
            {                                                                           \
                rhv[i] = mk2::simd::intrin::function::op_name(scalar, rhv[i]);          \
            }                                                                           \
            return rhv;                                                                 \
        }                                                                               \
        template <class Bits, class Type, std::size_t Size>                             \
        inline vectorizer_buffer<Bits, Type, Size> operator op(                         \
                vectorizer_buffer<Bits, Type, Size>&& lhv,                              \
                const Type rhv)                                                         \
        {                                                                               \
            constexpr std::size_t size = vectorizer<Bits, Type, Size>::mm_elems_size;   \
            decltype(auto) scalar = mk2::simd::intrin::function::set1<Bits>(rhv);       \
            for (std::size_t i = 0; i < size; i++)                                      \
            {                                                                           \
                lhv[i] = mk2::simd::intrin::function::op_name(lhv[i], scalar);          \
            }                                                                           \
            return lhv;                                                                 \
        }                                                                               \
        template <class Bits, class Type, std::size_t Size>                             \
        inline vectorizer_buffer<Bits, Type, Size> operator op(                         \
                vectorizer_buffer<Bits, Type, Size>&& lhv,                              \
                const vectorizer<Bits, Type, Size>& rhv)                                \
        {                                                                               \
            constexpr std::size_t size = vectorizer<Bits, Type, Size>::mm_elems_size;   \
            decltype(auto) mrhv = rhv.mm_data();                                        \
            for (std::size_t i = 0; i < size; i++)                                      \
            {                                                                           \
                lhv[i] = mk2::simd::intrin::function::op_name(lhv[i], mrhv[i]);         \
            }                                                                           \
            return lhv;                                                                 \
        }                                                                               \
        template <class Bits, class Type, std::size_t Size>                             \
        inline vectorizer_buffer<Bits, Type, Size> operator op(                         \
                const vectorizer<Bits, Type, Size>& lhv,                                \
                vectorizer_buffer<Bits, Type, Size>&& rhv)                              \
        {                                                                               \
            constexpr std::size_t size = vectorizer<Bits, Type, Size>::mm_elems_size;   \
            decltype(auto) mlhv = lhv.mm_data();                                        \
            for (std::size_t i = 0; i < size; i++)                                      \
            {                                                                           \
                rhv[i] = mk2::simd::intrin::function::op_name(mlhv[i], rhv[i]);         \
            }                                                                           \
            return rhv;                                                                 \
        }

        MK2_INTRIN_VECTORIZER_BUFFER_ARITHMETIC_OPERATOR_TEMPLETE(+, add)
        MK2_INTRIN_VECTORIZER_BUFFER_ARITHMETIC_OPERATOR_TEMPLETE(-, sub)
        MK2_INTRIN_VECTORIZER_BUFFER_ARITHMETIC_OPERATOR_TEMPLETE(*, mul)
        MK2_INTRIN_VECTORIZER_BUFFER_ARITHMETIC_OPERATOR_TEMPLETE(/ , div)

#undef MK2_INTRIN_VECTORIZER_BUFFER_ARITHMETIC_OPERATOR_TEMPLETE
            
    }
    
    // arithmetic operator
    // Sizeが1024以下だとはやい
#define MK2_INTRIN_VECTORIZER_ARITHMETIC_OPERATOR_TEMPLETE(op, op_name)             \
    template <class Bits, class Type, std::size_t Size>                             \
    inline detail::vectorizer_buffer<Bits, Type, Size> operator op(                 \
            const vectorizer<Bits, Type, Size>& lhv,                                \
            const vectorizer<Bits, Type, Size>& rhv)                                \
    {                                                                               \
        constexpr std::size_t size = vectorizer<Bits, Type, Size>::mm_elems_size;   \
        decltype(auto) mlhv = lhv.mm_data();                                        \
        decltype(auto) mrhv = rhv.mm_data();                                        \
        detail::vectorizer_buffer<Bits, Type, Size> container;                      \
        for (std::size_t i = 0; i < size; i++)                                      \
        {                                                                           \
            container[i] = mk2::simd::intrin::function::op_name(mlhv[i], mrhv[i]);  \
        }                                                                           \
        return container;                                                           \
    }                                                                               \
    template <class Bits, class Type, std::size_t Size>                             \
    inline detail::vectorizer_buffer<Bits, Type, Size> operator op(                 \
            const Type lhv,                                                         \
            const vectorizer<Bits, Type, Size>& rhv)                                \
    {                                                                               \
        constexpr std::size_t size = vectorizer<Bits, Type, Size>::mm_elems_size;   \
        decltype(auto) mlhv = mk2::simd::intrin::function::set1<Bits>(lhv);         \
        decltype(auto) mrhv = rhv.mm_data();                                        \
        detail::vectorizer_buffer<Bits, Type, Size> container;                      \
        for (std::size_t i = 0; i < size; i++)                                      \
        {                                                                           \
            container[i] = mk2::simd::intrin::function::op_name(mlhv, mrhv[i]);     \
        }                                                                           \
        return container;                                                           \
    }                                                                               \
    template <class Bits, class Type, std::size_t Size>                             \
    inline detail::vectorizer_buffer<Bits, Type, Size> operator op(                 \
            const vectorizer<Bits, Type, Size>& lhv,                                \
            const Type rhv)                                                         \
    {                                                                               \
        constexpr std::size_t size = vectorizer<Bits, Type, Size>::mm_elems_size;   \
        decltype(auto) mlhv = lhv.mm_data();                                        \
        decltype(auto) mrhv = mk2::simd::intrin::function::set1<Bits>(rhv);         \
        detail::vectorizer_buffer<Bits, Type, Size> container;                      \
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
