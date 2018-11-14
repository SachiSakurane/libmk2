//
// Created by Himatya on 2018-11-10.
//

#pragma once

#include <cstddef>
#include <utility>

#include <mk2/simd/intrin/vectorizer.hpp>
#include <mk2/simd/intrin/function/arithmetic.hpp>
#include <mk2/simd/intrin/function/set.hpp>
#include <mk2/simd/intrin/type_traits/architecture.hpp>
#include <mk2/simd/intrin/type_traits/bit_type.hpp>

namespace mk2 { namespace simd { namespace intrin {

    template <class Bits, class Type, std::size_t Size> class vectorizer;

    namespace detail
    {
#define MK2_LAZY_VECTORIZER_OPERATOR_STRUCT(name)                                           \
        struct lazy_vectorizer_##name                                                       \
        {                                                                                   \
            template <class LeftType, class RightType, class BufferType, std::size_t Size>  \
            static void calc(LeftType&& lhv, RightType&& rhv, BufferType* dest)             \
            {                                                                               \
                constexpr std::size_t contain_size =                                        \
                    sizeof(typename LeftType::mm_type) / sizeof(typename LeftType::type);   \
                constexpr std::size_t loop_size = Size / contain_size;                      \
                decltype(auto) l_buf = lhv.data();                                          \
                decltype(auto) r_buf = rhv.data();                                          \
                for (std::size_t i = 0; i < loop_size; ++i)                                 \
                {                                                                           \
                    dest[i] = mk2::simd::intrin::function::name(l_buf[i], r_buf[i]);        \
                }                                                                           \
            }                                                                               \
        };

        MK2_LAZY_VECTORIZER_OPERATOR_STRUCT(add)
        MK2_LAZY_VECTORIZER_OPERATOR_STRUCT(sub)
        MK2_LAZY_VECTORIZER_OPERATOR_STRUCT(mul)
        MK2_LAZY_VECTORIZER_OPERATOR_STRUCT(div)

#undef MK2_LAZY_VECTORIZER_OPERATOR_STRUCT

        template <class Type, class Enablar = void>
        struct is_add_or_sub { static constexpr bool value = false; };

        template <class Type>
        struct is_add_or_sub<Type, typename std::enable_if<
                std::is_same<typename Type::operator_type, lazy_vectorizer_mul>::value &&
                std::is_same<typename Type::operator_type, lazy_vectorizer_add>::value
        >::type>
        { static constexpr bool value = true; };

        template <class LeftType, class RightType, class Enablar = void>
        struct is_transformable_fma { static constexpr bool value = false; };

        template <class LeftType, class RightType>
        struct is_transformable_fma<LeftType, RightType, typename std::enable_if<
                (is_add_or_sub<LeftType>::value && std::is_same<typename RightType::operator_type, lazy_vectorizer_mul>::value) ||
                (is_add_or_sub<RightType>::value && std::is_same<typename LeftType::operator_type, lazy_vectorizer_mul>::value)
        >::type>
        { static constexpr bool value = true; };

        // データ取得の統一化
        // lazy_vectorizer
        template <class Bits, class Vectorizer, class Enabler = void>
        class lazy_vectorizer_buffer {};

        // OperatorがaddかsubでLeftTypeかRightTypeのOperatorがmulである場合はfmaに変換できる
        template <class Bits, class LeftType, class RightType, class Operator, std::size_t Size, class Enablar = void>
        struct lazy_vectorizer
        {
            using left_type = LeftType;
            using right_type = RightType;
            using operator_type = Operator;
            using left_buffer_type = lazy_vectorizer_buffer<Bits, left_type>;
            using right_buffer_type = lazy_vectorizer_buffer<Bits, right_type>;
            using type = typename left_buffer_type::type;
            using mm_type = typename left_buffer_type::mm_type;

            static constexpr std::size_t size() { return Size; }

            lazy_vectorizer(left_buffer_type&& lhv, right_buffer_type&& rhv) :
                    lhv_(std::move(lhv)), rhv_(std::move(rhv)){}

            template <class BufferType>
            void calc(BufferType* dest)
            {
                operator_type::template calc<left_buffer_type, right_buffer_type, BufferType, Size>(std::move(lhv_), std::move(rhv_), dest);
            }

            left_buffer_type  lhv_;
            right_buffer_type rhv_;
        };

        // fma
        template <class Bits, class LeftType, class RightType, class Operator, std::size_t Size>
        struct lazy_vectorizer<Bits, LeftType, RightType, Operator, Size,
                typename std::enable_if<mk2::simd::intrin::arch_fma::value && is_transformable_fma<LeftType, RightType>::value>::type>
        {
            using left_type = LeftType;
            using right_type = RightType;
            using operator_type = Operator;
            using left_buffer_type = lazy_vectorizer_buffer<Bits, left_type>;
            using right_buffer_type = lazy_vectorizer_buffer<Bits, right_type>;
            using type = typename left_buffer_type::type;
            using mm_type = typename left_type::mm_type;

            static constexpr std::size_t size() { return Size; }

            lazy_vectorizer(left_buffer_type&& lhv, right_buffer_type&& rhv) :
                    lhv_(std::move(lhv)), rhv_(std::move(rhv)){}

            template <class BufferType>
            void calc(BufferType* dest)
            {
                if constexpr (std::is_same<typename left_type::operator_type, lazy_vectorizer_mul>::value)
                {
                    if constexpr (std::is_same<typename right_type::operator_type, lazy_vectorizer_add>::value)
                    {
                        operator_type::fmadd<Size>(std::move(lhv_.lhv_), std::move(lhv_.rhv_), std::move(rhv_));
                    }
                    else
                    {
                        operator_type::fmsub<Size>(std::move(lhv_.lhv_), std::move(lhv_.rhv_), std::move(rhv_));
                    }
                }
                else
                {
                    if constexpr (std::is_same<typename left_type::operator_type, lazy_vectorizer_add>::value)
                    {
                        operator_type::fmadd<Size>(std::move(rhv_.lhv_), std::move(rhv_.rhv_), std::move(lhv_));
                    }
                    else
                    {
                        operator_type::fnmadd<Size>(std::move(rhv_.lhv_), std::move(rhv_.rhv_), std::move(lhv_));
                    }
                }
            }

            left_buffer_type  lhv_;
            right_buffer_type rhv_;
        };

        // vectorizer_buffer
        template <class Bits, class LeftType, class RightType, class Operator, std::size_t Size>
        class lazy_vectorizer_buffer<Bits, lazy_vectorizer<Bits, LeftType, RightType, Operator, Size>, void>
        {
        public:
            using vectorizer_type = lazy_vectorizer<Bits, LeftType, RightType, Operator, Size>;
            using type = typename vectorizer_type::type;
            using mm_type = typename vectorizer_type::mm_type;

            lazy_vectorizer_buffer(vectorizer_type&& v) : vectorizer_(std::move(v)) {}

            mm_type* data()
            {
                vectorizer_.calc(buffer_);
                return buffer_;
            }

        private:

            vectorizer_type vectorizer_;
            mm_type buffer_[Size / (sizeof(mm_type) / sizeof(type))];
        };

        // vectorizer
        template<class Bits, class Type, std::size_t Size>
        class lazy_vectorizer_buffer<Bits, vectorizer<Bits, Type, Size>, void>
        {
        public:
            using type = Type;
            using mm_type = typename vectorizer<Bits, Type, Size>::mm_type;

            lazy_vectorizer_buffer(const vectorizer<Bits, Type, Size>& v) : buffer_(v) {}

            decltype(auto) data() { return buffer_.mm_data(); }

        private:
            const mk2::simd::intrin::vectorizer<Bits, Type, Size>& buffer_;
        };

        // scalar
        template<class Bits, class Type>
        class lazy_vectorizer_buffer<Bits, Type, typename std::enable_if<std::is_arithmetic<Type>::value>::type>
        {
            struct scalar_assigner
            {
                using mm_type = typename mk2::simd::intrin::bit_type<Type, Bits>::type;

                scalar_assigner(Type v) : buffer_(mk2::simd::intrin::function::set1<Bits, Type>(v)) {}

                mm_type& operator[](std::size_t)
                {
                    return buffer_;
                }

                mm_type buffer_;
            };

        public:
            using type = Type;
            using mm_type = typename mk2::simd::intrin::bit_type<Type, Bits>::type;

            lazy_vectorizer_buffer(Type v) : buffer_(v) {}

            decltype(auto) data() { return buffer_; }

        private:
            scalar_assigner buffer_;
        };

#define MK2_LAZY_VECTORIZER_OPERATOR_FUNC_TEMPLATE(op, name)                                        \
        template <class Bits, class LeftType1, class LeftType2, class RightType1, class RightType2, \
                class Operator1, class Operator2, std::size_t Size>                                 \
        inline decltype(auto) operator op(                                                          \
                lazy_vectorizer<Bits, LeftType1, RightType1, Operator1, Size>&& lhv,                \
                lazy_vectorizer<Bits, LeftType2, RightType2, Operator2, Size>&& rhv)                \
        {                                                                                           \
            using l_type = lazy_vectorizer<Bits, LeftType1, RightType1, Operator1, Size>;           \
            using r_type = lazy_vectorizer<Bits, LeftType2, RightType2, Operator2, Size>;           \
            using l_lazy_type = lazy_vectorizer_buffer<Bits, l_type>;                               \
            using r_lazy_type = lazy_vectorizer_buffer<Bits, r_type>;                               \
            return lazy_vectorizer<Bits, l_type, r_type, lazy_vectorizer_##name, Size>(             \
                    l_lazy_type(std::move(lhv)),                                                    \
                    r_lazy_type(std::move(rhv)));                                                   \
        }                                                                                           \
        template <class Bits, class Type, class LeftType1, class RightType1,                        \
                class Operator1, std::size_t Size>                                                  \
        inline decltype(auto) operator op(                                                          \
                lazy_vectorizer<Bits, LeftType1, RightType1, Operator1, Size>&& lhv,                \
                Type rhv)                                                                           \
        {                                                                                           \
            using l_type = lazy_vectorizer<Bits, LeftType1, RightType1, Operator1, Size>;           \
            using l_lazy_type = lazy_vectorizer_buffer<Bits, l_type>;                               \
            using r_lazy_type = lazy_vectorizer_buffer<Bits, Type>;                                 \
            return lazy_vectorizer<Bits, l_type, Type, lazy_vectorizer_##name, Size>(               \
                    l_lazy_type(std::move(lhv)),                                                    \
                    r_lazy_type(rhv));                                                              \
        }                                                                                           \
        template <class Bits, class Type, class LeftType1, class RightType1,                        \
                class Operator1, std::size_t Size>                                                  \
        inline decltype(auto) operator op(                                                          \
                lazy_vectorizer<Bits, LeftType1, RightType1, Operator1, Size>&& lhv,                \
                const mk2::simd::intrin::vectorizer<Bits, Type, Size>& rhv)                         \
        {                                                                                           \
            using l_type = lazy_vectorizer<Bits, LeftType1, RightType1, Operator1, Size>;           \
            using vec_type = mk2::simd::intrin::vectorizer<Bits, Type, Size>;                       \
            using l_lazy_type = lazy_vectorizer_buffer<Bits, l_type>;                               \
            using r_lazy_type = lazy_vectorizer_buffer<Bits, vec_type>;                             \
            return lazy_vectorizer<Bits, l_type, vec_type, lazy_vectorizer_##name, Size>(           \
                    l_lazy_type(std::move(lhv)),                                                    \
                    r_lazy_type(rhv));                                                              \
        }                                                                                           \
        template <class Bits, class Type, class LeftType1, class RightType1,                        \
                class Operator1, std::size_t Size>                                                  \
        inline decltype(auto) operator op(                                                          \
                Type lhv,                                                                           \
                lazy_vectorizer<Bits, LeftType1, RightType1, Operator1, Size>&& rhv)                \
        {                                                                                           \
            using r_type = lazy_vectorizer<Bits, LeftType1, RightType1, Operator1, Size>;           \
            using l_lazy_type = lazy_vectorizer_buffer<Bits, Type>;                                 \
            using r_lazy_type = lazy_vectorizer_buffer<Bits, r_type>;                               \
            return lazy_vectorizer<Bits, Type, r_type, lazy_vectorizer_##name, Size>(               \
                    l_lazy_type(lhv),                                                               \
                    r_lazy_type(std::move(rhv)));                                                   \
        }                                                                                           \
        template <class Bits, class Type, class LeftType1, class RightType1,                        \
                class Operator1, std::size_t Size>                                                  \
        inline decltype(auto) operator op(                                                          \
                const mk2::simd::intrin::vectorizer<Bits, Type, Size>& lhv,                         \
                lazy_vectorizer<Bits, LeftType1, RightType1, Operator1, Size>&& rhv)                \
        {                                                                                           \
            using r_type = lazy_vectorizer<Bits, LeftType1, RightType1, Operator1, Size>;           \
            using vec_type = mk2::simd::intrin::vectorizer<Bits, Type, Size>;                       \
            using l_lazy_type = lazy_vectorizer_buffer<Bits, vec_type>;                             \
            using r_lazy_type = lazy_vectorizer_buffer<Bits, r_type>;                               \
            return lazy_vectorizer<Bits, vec_type, r_type, lazy_vectorizer_##name, Size>(           \
                    l_lazy_type(lhv),                                                               \
                    r_lazy_type(std::move(rhv)));                                                   \
        }

    MK2_LAZY_VECTORIZER_OPERATOR_FUNC_TEMPLATE(+, add)
    MK2_LAZY_VECTORIZER_OPERATOR_FUNC_TEMPLATE(-, sub)
    MK2_LAZY_VECTORIZER_OPERATOR_FUNC_TEMPLATE(*, mul)
    MK2_LAZY_VECTORIZER_OPERATOR_FUNC_TEMPLATE(/, div)

#undef MK2_LAZY_VECTORIZER_OPERATOR_FUNC_TEMPLATE
    }

#define MK2_LAZY_VECTORIZER_OPERATOR_TEMPLATE(op, name)                                             \
    template <class Bits, class Type, std::size_t Size>                                             \
    inline decltype(auto) operator op(                                                              \
            const mk2::simd::intrin::vectorizer<Bits, Type, Size>& lhv,                             \
            const mk2::simd::intrin::vectorizer<Bits, Type, Size>& rhv)                             \
    {                                                                                               \
        using v_type = vectorizer<Bits, Type, Size>;                                                \
        return detail::lazy_vectorizer<Bits, v_type, v_type, detail::lazy_vectorizer_##name, Size>( \
                detail::lazy_vectorizer_buffer<Bits, v_type>(lhv),                                  \
                detail::lazy_vectorizer_buffer<Bits, v_type>(rhv));                                 \
    }                                                                                               \
    template <class Bits, class Type, std::size_t Size>                                             \
    inline decltype(auto) operator op(                                                              \
            const mk2::simd::intrin::vectorizer<Bits, Type, Size>& lhv, Type rhv)                   \
    {                                                                                               \
        using v_type = vectorizer<Bits, Type, Size>;                                                \
        return detail::lazy_vectorizer<Bits, v_type, Type, detail::lazy_vectorizer_##name, Size>(   \
                detail::lazy_vectorizer_buffer<Bits, v_type>(lhv),                                  \
                detail::lazy_vectorizer_buffer<Bits, Type>(rhv));                                   \
    }                                                                                               \
    template <class Bits, class Type, std::size_t Size>                                             \
    inline decltype(auto) operator op(                                                              \
            Type lhv, const mk2::simd::intrin::vectorizer<Bits, Type, Size>& rhv)                   \
    {                                                                                               \
        using v_type = vectorizer<Bits, Type, Size>;                                                \
        return detail::lazy_vectorizer<Bits, Type, v_type, detail::lazy_vectorizer_##name, Size>(   \
                detail::lazy_vectorizer_buffer<Bits, Type>(lhv),                                    \
                detail::lazy_vectorizer_buffer<Bits, v_type>(rhv));                                 \
    }

    MK2_LAZY_VECTORIZER_OPERATOR_TEMPLATE(+, add)
    MK2_LAZY_VECTORIZER_OPERATOR_TEMPLATE(-, sub)
    MK2_LAZY_VECTORIZER_OPERATOR_TEMPLATE(*, mul)
    MK2_LAZY_VECTORIZER_OPERATOR_TEMPLATE(/, div)

#undef MK2_LAZY_VECTORIZER_OPERATOR_TEMPLATE

}}}