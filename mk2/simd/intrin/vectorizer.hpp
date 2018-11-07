//
// Created by Himatya on 2018-10-29.
//

#pragma once

#include <mk2/iterator/data.hpp>
#include <mk2/iterator/index_iterator.hpp>
#include <mk2/simd/intrin/detail/vectorizer_buffer.hpp>
#include <mk2/simd/intrin/function/arithmetic.hpp>
#include <mk2/simd/intrin/function/assignment.hpp>
#include <mk2/simd/intrin/function/comparison.hpp>
#include <mk2/simd/intrin/function/logical.hpp>
#include <mk2/simd/intrin/function/set.hpp>
#include <mk2/simd/intrin/function/swap.hpp>
#include <mk2/simd/intrin/type_traits/bit_type.hpp>

namespace mk2 { namespace simd { namespace intrin
{
    // 外見の振る舞いとしてはType型のコンテナのようにふるまう
    template <class Type, class Bits, size_t Size, class Align = mk2::simd::intrin::is_aligned<false>>
    class vectorizer
    {
    public:
        using mm_type = typename mk2::simd::intrin::bit_type<Type, Bits>::type;
        static constexpr std::size_t mm_contain_size = sizeof(mm_type) / sizeof(Type);
        static constexpr std::size_t mm_elems_size = Size / mm_contain_size;

        using value_type = Type;
        using reference = value_type&;
        using const_reference = const value_type&;
        using iterator = mk2::iterator::index_iterator<vectorizer>;
        using const_iterator = mk2::iterator::index_iterator<const vectorizer>;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        //using allocator_type = Allocator;
    
        // constructors
        vectorizer();
        
        vectorizer(const vectorizer& ) = default;
        vectorizer(vectorizer&& ) noexcept = default;

        template <class Container>
        explicit vectorizer(const Container& c);
        explicit vectorizer(const_pointer data);
        explicit vectorizer(mm_type* mm_data);
        explicit vectorizer(detail::vectorizer_buffer<Type, Bits, Size, Align>&& buf);

        // destructor
        virtual ~vectorizer() = default;
        
        // assignment operator
        vectorizer& operator=(const vectorizer& ) = default;
        vectorizer& operator=(vectorizer&& )noexcept = default;

        vectorizer& operator=(detail::vectorizer_buffer<Type, Bits, Size, Align>&& buf);
        
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
        reference operator[](size_t n) noexcept { return data()[n]; }

        const_reference operator[](size_t n) const noexcept { return data()[n]; }

        reference at(size_t n)
        { return n < Size ? (*this)[n] : throw std::out_of_range("fixed_array::at"); }

        const_reference at(size_t n) const
        { return n < Size ? (*this)[n] : throw std::out_of_range("fixed_array::at"); }
        
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
        template <class Container>
        void load(const Container& p);
        void load(pointer p);
        
        template <class Container>
        void store(const Container& c);
        void store(pointer p);
        void fill(value_type value);
        void swap(vectorizer& other) noexcept(std::is_nothrow_swappable<mm_type>::value);
        
    private:
        template<size_t... Indices>
        vectorizer(const Type* data, std::index_sequence<Indices...>);

        template<size_t... Indices>
        vectorizer(mm_type* data, std::index_sequence<Indices...>);

        mm_type elems_[mm_elems_size];
    };
    
    // constructors
    template <class Type, class Bits, size_t Size, class Align>
    vectorizer<Type, Bits, Size, Align>::vectorizer() : elems_{ {mk2::simd::intrin::function::setzero<Bits, Type>()} }
    {}
    
    template <class Type, class Bits, size_t Size, class Align>
    template <class Container>
    vectorizer<Type, Bits, Size, Align>::vectorizer(const Container& c) : vectorizer(c.data())
    {
        // static_assert(c.size() >= Size);
    }
    
    template <class Type, class Bits, size_t Size, class Align>
    vectorizer<Type, Bits, Size, Align>::vectorizer(const Type* data)
            : vectorizer(data, std::make_index_sequence<vectorizer<Type, Bits, Size, Align>::mm_elems_size>())
    {}
    
    template <class Type, class Bits, size_t Size, class Align>
    template<size_t... Indices>
    vectorizer<Type, Bits, Size, Align>::vectorizer(const Type* data, std::index_sequence<Indices...>)
            : elems_{ mk2::simd::intrin::function::load<Bits, Type, Align>(data + Indices * mm_contain_size)... }
    {}

    template <class Type, class Bits, size_t Size, class Align>
    vectorizer<Type, Bits, Size, Align>::vectorizer(typename vectorizer<Type, Bits, Size, Align>::mm_type* data)
            : vectorizer(data, std::make_index_sequence<vectorizer<Type, Bits, Size, Align>::mm_elems_size>())
    {}

    template <class Type, class Bits, size_t Size, class Align>
    template<size_t... Indices>
    vectorizer<Type, Bits, Size, Align>::vectorizer(typename vectorizer<Type, Bits, Size, Align>::mm_type* data, std::index_sequence<Indices...>)
            : elems_{ data[Indices]... }
    {}

    template <class Type, class Bits, size_t Size, class Align>
    vectorizer<Type, Bits, Size, Align>::vectorizer(detail::vectorizer_buffer<Type, Bits, Size, Align>&& buf)
            : vectorizer(buf.container, std::make_index_sequence<vectorizer<Type, Bits, Size, Align>::mm_elems_size>())
    {}

    // assign
    template <class Type, class Bits, size_t Size, class Align>
    vectorizer<Type, Bits, Size, Align>& vectorizer<Type, Bits, Size, Align>::operator=(detail::vectorizer_buffer<Type, Bits, Size, Align>&& buf)
    {
        *this = vectorizer<Type, Bits, Size, Align>(std::move(buf));
        return *this;
    }
    
    // operation
    template <class Type, class Bits, size_t Size, class Align>
    template <class Container>
    void vectorizer<Type, Bits, Size, Align>::load(const Container& c)
    {
        this->load(mk2::iterator::data(c));
    }

    template <class Type, class Bits, size_t Size, class Align>
    void vectorizer<Type, Bits, Size, Align>::load(typename vectorizer<Type, Bits, Size, Align>::pointer p)
    {
        for (std::size_t i = 0; i < mm_elems_size; i++)
        {
            elems_[i] = mk2::simd::intrin::function::load<Bits, Align>(p + i * mm_contain_size);
        }
    }

    template <class Type, class Bits, size_t Size, class Align>
    template <class Container>
    void vectorizer<Type, Bits, Size, Align>::store(const Container& c)
    {
        this->store(mk2::iterator::data(c));
    }

    template <class Type, class Bits, size_t Size, class Align>
    void vectorizer<Type, Bits, Size, Align>::store(typename vectorizer<Type, Bits, Size, Align>::pointer p)
    {
        for (std::size_t i = 0; i < mm_elems_size; i++)
        {
            mk2::simd::intrin::function::store<Align>(p + i * mm_contain_size, elems_ + i);
        }
    }

    template <class Type, class Bits, size_t Size, class Align>
    void vectorizer<Type, Bits, Size, Align>::fill(Type value)
    {
        for (std::size_t i = 0; i < mm_elems_size; i++)
        {
            elems_[i] = mk2::simd::intrin::function::set1<mm_type>(value);
        }
    }

    template <class Type, class Bits, size_t Size, class Align>
    void vectorizer<Type, Bits, Size, Align>::swap(vectorizer<Type, Bits, Size, Align>& other)
        noexcept(std::is_nothrow_swappable<vectorizer<Type, Bits, Size, Align>::mm_type>::value)
    {
        for (std::size_t i = 0; i < mm_elems_size; i++)
        {
            mk2::simd::intrin::function::swap(elems_[i], other.mm_data()[i]);
        }
    }
    
    // comparison operator
    template <class Type, class Bits, size_t Size, class Align>
    inline bool operator==(const vectorizer<Type, Bits, Size, Align>& lhv, const vectorizer<Type, Bits, Size, Align>& rhv)
    {
        decltype(auto) mlhv = lhv.mm_data();
        decltype(auto) mrhv = rhv.mm_data();
        const auto zero = mk2::simd::intrin::function::setzero<vectorizer<Type, Bits, Size, Align>::mm_type>();

        for (std::size_t i = 0; i < vectorizer<Type, Bits, Size, Align>::mm_elems_size; i++)
        {
            if (mk2::simd::intrin::function::testc(zero, mk2::simd::intrin::function::cmp_neq(mlhv[i], mrhv[i])))
                return false;
        }
        return true;
    }

    template <class Type, class Bits, size_t Size, class Align>
    inline bool operator!=(const vectorizer<Type, Bits, Size, Align>& lhv, const vectorizer<Type, Bits, Size, Align>& rhv)
    {
        return !operator==(lhv, rhv);
    }

    template <class Type, class Bits, size_t Size, class Align>
    inline bool operator<(const vectorizer<Type, Bits, Size, Align>& lhv, const vectorizer<Type, Bits, Size, Align>& rhv)
    {
        decltype(auto) mlhv = lhv.mm_data();
        decltype(auto) mrhv = rhv.mm_data();
        const auto zero = mk2::simd::intrin::function::setzero<vectorizer<Type, Bits, Size, Align>::mm_type>();

        for (std::size_t i = 0; i < vectorizer<Type, Bits, Size, Align>::mm_elems_size; i++)
        {
            if (mk2::simd::intrin::function::testc(zero, mk2::simd::intrin::function::cmp_nlt(mlhv[i], mrhv[i])))
                return false;
        }
        return true;
    }

    template <class Type, class Bits, size_t Size, class Align>
    inline bool operator<=(const vectorizer<Type, Bits, Size, Align>& lhv, const vectorizer<Type, Bits, Size, Align>& rhv)
    {
        decltype(auto) mlhv = lhv.mm_data();
        decltype(auto) mrhv = rhv.mm_data();
        const auto zero = mk2::simd::intrin::function::setzero<vectorizer<Type, Bits, Size, Align>::mm_type>();

        for (std::size_t i = 0; i < vectorizer<Type, Bits, Size, Align>::mm_elems_size; i++)
        {
            if (mk2::simd::intrin::function::testc(zero, mk2::simd::intrin::function::cmp_nle(mlhv[i], mrhv[i])))
                return false;
        }
        return true;
    }

    template <class Type, class Bits, size_t Size, class Align>
    inline bool operator>(const vectorizer<Type, Bits, Size, Align>& lhv, const vectorizer<Type, Bits, Size, Align>& rhv)
    {
        return !operator<=(lhv, rhv);
    } 

    template <class Type, class Bits, size_t Size, class Align>
    inline bool operator>=(const vectorizer<Type, Bits, Size, Align>& lhv, const vectorizer<Type, Bits, Size, Align>& rhv)
    {
        return !operator<(lhv, rhv);
    }
}}}