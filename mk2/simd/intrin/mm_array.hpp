//
// Created by Himatya on 2018-10-29.
//

#pragma once

#include <mk2/iterator/data.hpp>
#include <mk2/iterator/index_iterator.hpp>
#include <mk2/simd/intrin/include.hpp>
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
    class mm_array
    {
    public:
        using mm_type = typename mk2::simd::intrin::bit_type<Type, Bits>::type;
        static constexpr std::size_t mm_contain_size = sizeof(mm_type) / sizeof(Type);
        static constexpr std::size_t mm_elems_size = Size / mm_contain_size;

        using value_type = Type;
        using reference = value_type&;
        using const_reference = const value_type&;
        using iterator = mk2::iterator::index_iterator<mm_array>;
        using const_iterator = mk2::iterator::index_iterator<const mm_array>;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        //using allocator_type = Allocator;
    
        // constructors
        mm_array();
        
        mm_array(const mm_array& ) = default;
        mm_array(mm_array&& ) noexcept = default;

        template <class Container>
        explicit mm_array(const Container& c);
        explicit mm_array(const value_type* data);

        // destructor
        virtual ~mm_array() = default;
        
        // assignment operator
        mm_array& operator=(const mm_array& ) = default;
        mm_array& operator=(mm_array&& )noexcept = default;
        
        pointer operator=(pointer lhv);
        
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
        reference operator[](size_t n) noexcept { return elems_[n / mm_elems_size][n % mm_contain_size]; }

        const_reference operator[](size_t n) const noexcept { return elems_[n / mm_elems_size][n % mm_contain_size]; }

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
        void swap(mm_array& other) noexcept(std::is_nothrow_swappable<mm_type>::value);
        
    private:
        template<size_t... Indices>
        mm_array(const Type* data, std::index_sequence<Indices...>);
    
        mm_type elems_[mm_elems_size];
    };
    
    // constructors
    template <class Type, class Bits, size_t Size, class Align>
    mm_array<Type, Bits, Size, Align>::mm_array() : elems_{ {mk2::simd::intrin::function::setzero<mm_type>()} }
    {}
    
    template <class Type, class Bits, size_t Size, class Align>
    template <class Container>
    mm_array<Type, Bits, Size, Align>::mm_array(const Container& c) : mm_array(c.data())
    {
        static_assert(c.size() >= Size);
    }
    
    template <class Type, class Bits, size_t Size, class Align>
    mm_array<Type, Bits, Size, Align>::mm_array(const Type* data) : mm_array(data, std::make_index_sequence<Size>())
    {}
    
    template <class Type, class Bits, size_t Size, class Align>
    template<size_t... Indices>
    mm_array<Type, Bits, Size, Align>::mm_array(const Type* data, std::index_sequence<Indices...>)
        : elems_{ mk2::simd::intrin::function::load<Bits, Align>(data + Indices * mm_contain_size)... }
    {}
    
    // assignment operator
    template <class Type, class Bits, size_t Size, class Align>
    typename mm_array<Type, Bits, Size, Align>::pointer mm_array<Type, Bits, Size, Align>::operator=(typename mm_array<Type, Bits, Size, Align>::pointer lhv)
    {
        this->store(lhv);
        return lhv;
    }
    
    // operation
    template <class Type, class Bits, size_t Size, class Align>
    template <class Container>
    void mm_array<Type, Bits, Size, Align>::load(const Container& c)
    {
        this->load(mk2::iterator::data(c));
    }

    template <class Type, class Bits, size_t Size, class Align>
    void mm_array<Type, Bits, Size, Align>::load(typename mm_array<Type, Bits, Size, Align>::pointer p)
    {
        for (std::size_t i = 0; i < mm_elems_size; i++)
        {
            elems_[i] = mk2::simd::intrin::function::load<Bits, Align>(p + i * mm_contain_size);
        }
    }

    template <class Type, class Bits, size_t Size, class Align>
    template <class Container>
    void mm_array<Type, Bits, Size, Align>::store(const Container& c)
    {
        this->store(mk2::iterator::data(c));
    }

    template <class Type, class Bits, size_t Size, class Align>
    void mm_array<Type, Bits, Size, Align>::store(typename mm_array<Type, Bits, Size, Align>::pointer p)
    {
        for (std::size_t i = 0; i < mm_elems_size; i++)
        {
            mk2::simd::intrin::function::store<Align>(p + i * mm_contain_size, elems_ + i);
        }
    }

    template <class Type, class Bits, size_t Size, class Align>
    void mm_array<Type, Bits, Size, Align>::fill(Type value)
    {
        for (std::size_t i = 0; i < mm_elems_size; i++)
        {
            elems_[i] = mk2::simd::intrin::function::set1<Bits>(value);
        }
    }

    template <class Type, class Bits, size_t Size, class Align>
    void mm_array<Type, Bits, Size, Align>::swap(mm_array<Type, Bits, Size, Align>& other)
        noexcept(std::is_nothrow_swappable<mm_array<Type, Bits, Size, Align>::mm_type>::value)
    {
        for (std::size_t i = 0; i < mm_elems_size; i++)
        {
            mk2::simd::intrin::function::swap(elems_[i], other.mm_data()[i]);
        }
    }
    
    // operator
    template <class Type, class Bits, size_t Size, class Align>
            inline bool operator==(const mm_array<Type, Bits, Size, Align>& x, const mm_array<Type, Bits, Size, Align>& y)
            {
                decltype(auto) mm_x = x.mm_data();
                decltype(auto) mm_y = y.mm_data();
                const auto zero = mk2::simd::intrin::function::setzero<mm_array<Type, Bits, Size, Align>::mm_type>();

                for (std::size_t i = 0; i < mm_array<Type, Bits, Size, Align>::mm_elems_size; i++)
                {
                    if (mk2::simd::intrin::function::bit_testc(zero, mk2::simd::intrin::function::cmp_neq(mm_x, mm_y)))
                        return false;
                }
                return true;
            }

    template <class Type, class Bits, size_t Size, class Align>
    inline bool operator!=(const mm_array<Type, Bits, Size, Align>& x, const mm_array<Type, Bits, Size, Align>& y)
    {
        return !operator==(x, y);
    }



}}}