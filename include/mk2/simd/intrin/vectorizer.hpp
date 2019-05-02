//
// Created by Himatya on 2018-10-29.
//

#pragma once

#include <cstddef>
#include <iterator>

#include <mk2/iterator/data.hpp>
#include <mk2/iterator/index_iterator.hpp>
#include <mk2/simd/intrin/detail/lazy_vectorizer_operation.hpp>
#include <mk2/simd/intrin/function/arithmetic.hpp>
#include <mk2/simd/intrin/function/assignment.hpp>
#include <mk2/simd/intrin/function/comparison.hpp>
#include <mk2/simd/intrin/function/logical.hpp>
#include <mk2/simd/intrin/function/set.hpp>
#include <mk2/simd/intrin/function/swap.hpp>
#include <mk2/simd/intrin/type_traits/alignment.hpp>
#include <mk2/simd/intrin/type_traits/bit_type.hpp>

namespace mk2 { namespace simd { namespace intrin
{
    template <class Bits, class Type, std::size_t Size>
    class vectorizer
    {
    public:
        using value_type = Type;
        using reference = value_type & ;
        using const_reference = const value_type&;
        using iterator = mk2::iterator::index_iterator<vectorizer>;
        using const_iterator = mk2::iterator::index_iterator<const vectorizer>;
        using pointer = value_type * ;
        using const_pointer = const value_type*;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        using mm_type = typename mk2::simd::intrin::bit_type<value_type, Bits>::type;
        static constexpr std::size_t mm_contain_size = sizeof(mm_type) / sizeof(value_type);
        static constexpr std::size_t mm_elems_size = Size / mm_contain_size;

        // constructors
        vectorizer();

        vectorizer(const vectorizer&) = default;
        vectorizer(vectorizer&&) noexcept = default;

        template <class Container>
        explicit vectorizer(const Container& c);
        explicit vectorizer(const_pointer data);
        explicit vectorizer(mm_type* mm_data);

        template <class LeftType, class RightType, class Operator>
        explicit vectorizer(detail::lazy_vectorizer<Bits, LeftType, RightType, Operator, Size>&& buf);

        // destructor
        virtual ~vectorizer() = default;

        // assignment operator
        vectorizer& operator=(const vectorizer&) = default;
        vectorizer& operator=(vectorizer&&)noexcept = default;

        template <class LeftType, class RightType, class Operator>
        vectorizer& operator=(detail::lazy_vectorizer<Bits, LeftType, RightType, Operator, Size>&& buf);

        // iterator
        iterator begin() noexcept { return iterator(*this, 0); }

        const_iterator begin() const noexcept { return const_iterator(*this, 0); }

        iterator end() noexcept { return iterator(*this, Size); }

        const_iterator end() const noexcept { return const_iterator(*this, Size); }

        reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

        const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }

        reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

        const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

        const_iterator cbegin() const noexcept { return begin(); }

        const_iterator cend() const noexcept { return end(); }

        const_reverse_iterator crbegin() const noexcept { return rbegin(); }

        const_reverse_iterator crend() const noexcept { return rend(); }

        // access
        reference operator[](std::size_t n) noexcept { return data()[n]; }

        const_reference operator[](std::size_t n) const noexcept { return data()[n]; }

        reference at(std::size_t n)
        {
            return n < Size ? (*this)[n] : throw std::out_of_range("fixed_array::at");
        }

        const_reference at(std::size_t n) const
        {
            return n < Size ? (*this)[n] : throw std::out_of_range("fixed_array::at");
        }

        reference front() noexcept { return (*this)[0]; }
        const_reference front() const noexcept { return (*this)[0]; }

        reference back() noexcept { return (*this)[Size > 0 ? Size - 1 : 0]; }
        const_reference back() const noexcept { return (*this)[Size > 0 ? Size - 1 : 0]; }

        pointer data() { return reinterpret_cast<value_type*>(elems_); }
        const_pointer data() const { return reinterpret_cast<value_type*>(elems_); }

        mm_type* mm_data() noexcept { return elems_; }
        const mm_type* mm_data() const noexcept { return elems_; }

        // capacity
        constexpr size_type size() const noexcept { return Size; }
        constexpr size_type max_size() const noexcept { return Size; }
        constexpr bool empty() const noexcept { return Size == 0; }

        // operation
        template <class Container, class Align> void load(const Container& p);
        template <class Align> void load(pointer p);

        template <class Container, class Align> void store(const Container& c);
        template <class Align> void store(pointer p);

        void fill(value_type value);
        void swap(vectorizer& other) noexcept(std::is_nothrow_swappable<vectorizer<Bits, Type, Size>::mm_type>::value);

    private:

        template<std::size_t... Indices>
        vectorizer(const Type* data, std::index_sequence<Indices...>);

        template<std::size_t... Indices>
        vectorizer(mm_type* data, std::index_sequence<Indices...>);

        mm_type elems_[mm_elems_size];
    };

    // constructors
    template <class Bits, class Type, std::size_t Size>
    vectorizer<Bits, Type, Size>::vectorizer() : elems_{ { mk2::simd::intrin::function::setzero<Bits, Type>() } }
    {}

    template <class Bits, class Type, std::size_t Size>
    template <class Container>
    vectorizer<Bits, Type, Size>::vectorizer(const Container& c) : vectorizer(c.data())
    {
        // static_assert(c.size() >= Size);
    }

    template <class Bits, class Type, std::size_t Size>
    vectorizer<Bits, Type, Size>::vectorizer(const Type* data)
        : vectorizer(data, std::make_index_sequence<vectorizer<Bits, Type, Size>::mm_elems_size>())
    {}

    template <class Bits, class Type, std::size_t Size>
    template<std::size_t... Indices>
    vectorizer<Bits, Type, Size>::vectorizer(const Type* data, std::index_sequence<Indices...>)
        : elems_{ mk2::simd::intrin::function::load<Bits, Type>(data + Indices * mm_contain_size)... }
    {}

    template <class Bits, class Type, std::size_t Size>
    vectorizer<Bits, Type, Size>::vectorizer(typename vectorizer<Bits, Type, Size>::mm_type* data)
        : vectorizer(data, std::make_index_sequence<vectorizer<Bits, Type, Size>::mm_elems_size>())
    {}

    template <class Bits, class Type, std::size_t Size>
    template<std::size_t... Indices>
    vectorizer<Bits, Type, Size>::vectorizer(typename vectorizer<Bits, Type, Size>::mm_type* data, std::index_sequence<Indices...>)
        : elems_{ data[Indices]... }
    {}
    /*
    template <class Bits, class Type, std::size_t Size>
    vectorizer<Bits, Type, Size>::vectorizer(detail::vectorizer_buffer<Bits, Type, Size>&& buf)
        : vectorizer(buf.container, std::make_index_sequence<vectorizer<Bits, Type, Size>::mm_elems_size>())
    {}
    
    // assign
    template <class Bits, class Type, std::size_t Size>
    vectorizer<Bits, Type, Size>& vectorizer<Bits, Type, Size>::operator=(detail::vectorizer_buffer<Bits, Type, Size>&& buf)
    {
        *this = vectorizer<Bits, Type, Size>(std::move(buf));
        return *this;
    }*/
    template <class Bits, class Type, std::size_t Size>
    template <class LeftType, class RightType, class Operator>
    vectorizer<Bits, Type, Size>::vectorizer(detail::lazy_vectorizer<Bits, LeftType, RightType, Operator, Size>&& buf)
        : vectorizer()
    {
        buf.calc(this->mm_data());
    }

    // assign
    template <class Bits, class Type, std::size_t Size>
    template <class LeftType, class RightType, class Operator>
    vectorizer<Bits, Type, Size>& vectorizer<Bits, Type, Size>::operator=
            (detail::lazy_vectorizer<Bits, LeftType, RightType, Operator, Size>&& buf)
    {
        buf.calc(this->mm_data());
        return *this;
    }
    
    // operation
    template <class Bits, class Type, std::size_t Size>
    template <class Container, class Align>
    void vectorizer<Bits, Type, Size>::load(const Container& c)
    {
        this->load<Align>(mk2::iterator::data(c));
    }

    template <class Bits, class Type, std::size_t Size>
    template <class Align>
    void vectorizer<Bits, Type, Size>::load(typename vectorizer<Bits, Type, Size>::pointer p)
    {
        for (std::size_t i = 0; i < mm_elems_size; i++)
        {
            elems_[i] = mk2::simd::intrin::function::load<Bits, Align>(p + i * mm_contain_size);
        }
    }

    template <class Bits, class Type, std::size_t Size>
    template <class Container, class Align>
    void vectorizer<Bits, Type, Size>::store(const Container& c)
    {
        this->store<Align>(mk2::iterator::data(c));
    }

    template <class Bits, class Type, std::size_t Size>
    template <class Align>
    void vectorizer<Bits, Type, Size>::store(typename vectorizer<Bits, Type, Size>::pointer p)
    {
        for (std::size_t i = 0; i < mm_elems_size; i++)
        {
            mk2::simd::intrin::function::store<Align>(p + i * mm_contain_size, elems_ + i);
        }
    }

    template <class Bits, class Type, std::size_t Size>
    void vectorizer<Bits, Type, Size>::fill(Type value)
    {
        for (std::size_t i = 0; i < mm_elems_size; i++)
        {
            elems_[i] = mk2::simd::intrin::function::set1<mm_type>(value);
        }
    }

    template <class Bits, class Type, std::size_t Size>
    void vectorizer<Bits, Type, Size>::swap(vectorizer<Bits, Type, Size>& other)
        noexcept(std::is_nothrow_swappable<vectorizer<Bits, Type, Size>::mm_type>::value)
    {
        for (std::size_t i = 0; i < mm_elems_size; i++)
        {
            mk2::simd::intrin::function::swap(elems_[i], other.mm_data()[i]);
        }
    }

    // comparison operator
    template <class Bits, class Type, std::size_t Size>
    inline bool operator==(const vectorizer<Bits, Type, Size>& lhv, const vectorizer<Bits, Type, Size>& rhv)
    {
        decltype(auto) mlhv = lhv.mm_data();
        decltype(auto) mrhv = rhv.mm_data();
        const auto zero = mk2::simd::intrin::function::setzero<Bits, Type>();

        for (std::size_t i = 0; i < vectorizer<Bits, Type, Size>::mm_elems_size; i++)
        {
            if (mk2::simd::intrin::function::testc(zero, mk2::simd::intrin::function::cmp_eq(mlhv[i], mrhv[i])))
                return false;
        }
        return true;
    }

    template <class Bits, class Type, std::size_t Size>
    inline bool operator!=(const vectorizer<Bits, Type, Size>& lhv, const vectorizer<Bits, Type, Size>& rhv)
    {
        return !operator==(lhv, rhv);
    }

    template <class Bits, class Type, std::size_t Size>
    inline bool operator<(const vectorizer<Bits, Type, Size>& lhv, const vectorizer<Bits, Type, Size>& rhv)
    {
        decltype(auto) mlhv = lhv.mm_data();
        decltype(auto) mrhv = rhv.mm_data();
        const auto zero = mk2::simd::intrin::function::setzero<vectorizer<Bits, Type, Size>::mm_type>();

        for (std::size_t i = 0; i < vectorizer<Bits, Type, Size>::mm_elems_size; i++)
        {
            if (mk2::simd::intrin::function::testc(zero, mk2::simd::intrin::function::cmp_lt(mlhv[i], mrhv[i])))
                return false;
        }
        return true;
    }

    template <class Bits, class Type, std::size_t Size>
    inline bool operator<=(const vectorizer<Bits, Type, Size>& lhv, const vectorizer<Bits, Type, Size>& rhv)
    {
        decltype(auto) mlhv = lhv.mm_data();
        decltype(auto) mrhv = rhv.mm_data();
        const auto zero = mk2::simd::intrin::function::setzero<vectorizer<Bits, Type, Size>::mm_type>();

        for (std::size_t i = 0; i < vectorizer<Bits, Type, Size>::mm_elems_size; i++)
        {
            if (mk2::simd::intrin::function::testc(zero, mk2::simd::intrin::function::cmp_le(mlhv[i], mrhv[i])))
                return false;
        }
        return true;
    }

    template <class Bits, class Type, std::size_t Size>
    inline bool operator>(const vectorizer<Bits, Type, Size>& lhv, const vectorizer<Bits, Type, Size>& rhv)
    {
        return !operator<=(lhv, rhv);
    }

    template <class Bits, class Type, std::size_t Size>
    inline bool operator>=(const vectorizer<Bits, Type, Size>& lhv, const vectorizer<Bits, Type, Size>& rhv)
    {
        return !operator<(lhv, rhv);
    }

}}}