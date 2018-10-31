//
// Created by Himatya on 2018-10-29.
//

#pragma once

#include <mk2/simd/intrin/include.hpp>
#include <mk2/simd/intrin/mm_type.hpp>
#include <mk2/simd/intrin/function/load.hpp>
#include <mk2/simd/intrin/function/setzero.hpp>
#include <mk2/simd/intrin/function/store.hpp>

namespace mk2 { namespace simd { namespace intrin
{

    template <class Type, class Bits, size_t Size, bool Aligned = false>
    class mm_array
    {
        using mm_type = mk2::simd::intrin::mm_type<Type, Bits>::type;
        constexpr std::size_t mm_contain_size = sizeof(mm_type) / sizeof(Type);
        constexpr std::size_t mm_elems_size = Size / mm_contain_size;

    public:
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
        using allocator_type = Allocator;
    
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


        // 
        void store(pointer obj);
        
    private:
        template<size_t... Indices>
        mm_array(const Type* data, std::index_sequence<Indices...>);
    
        mm_type elems_[mm_elems_size];

    };
    
    // constructors
    template <class Type, class Bits, size_t Size, bool Aligned>
    mm_array<Type, Bits, Size, Aligned>::mm_array() : elems_{ {mk2::simd::intrin::function::setzero<mm_type>()} }
    {}
    
    template <class Type, class Bits, size_t Size, bool Aligned>
    template <class Container>
    mm_array<Type, Bits, Size, Aligned>::mm_array(const Container& c) : mm_array{ c.data() }
    {
        static_assert(c.size() >= Size);
    }
    
    template <class Type, class Bits, size_t Size, bool Aligned>
    mm_array<Type, Bits, Size, Aligned>::mm_array(const Type* data) : mm_array(data, std::make_index_sequence<Size>())
    {}
    
    template <class Type, class Bits, size_t Size, bool Aligned>
    template<size_t... Indices>
    mm_array<Type, Bits, Size, Aligned>::mm_array(const Type* data, std::index_sequence<Indices...>)
        : elems_{mk2::simd::intrin::function::load<Bits, Aligned>(data + Indices * mm_contain_size)...}
    {}
    
    // assignment operator
    template <class Type, class Bits, size_t Size, bool Aligned>
    typename mm_array<Type, Bits, Size, Aligned>::pointer mm_array<Type, Bits, Size>::operator=(typename mm_array<Type, Bits, Size, Aligned>::pointer lhv)
    {
        this->store(lhv);
        return lhv;
    }
    
    // 
    template <class Type, class Bits, size_t Size, bool Aligned>
    void mm_array<Type, Bits, Size>::store(typename mm_array<Type, Bits, Size, Aligned>::pointer obj)
    {
        for (std::size_t i = 0; i < mm_elems_size; i++)
        {
            mk2::simd::intrin::function::store<Aligned>(lhv + i * mm_contain_size, elems_ + i);
        }
    }
}}}