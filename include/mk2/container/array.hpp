//
//  array.hpp
//
//
//  Created by Himatya on 2017/01/20.
//  Copyright © 2016年 Himatya. All rights reserved.
//

#pragma once

#include <stdexcept>
#include <type_traits>
#include <iterator>

#include <mk2/container/indexes_tuple.hpp>
#include <mk2/iterator/index_iterator.hpp>
#include <mk2/iterator/distance.hpp>

namespace mk2{
namespace container{
    
    namespace detail{
        template<class T, std::size_t Size>
        struct array_impl
        {
            constexpr array_impl() : elems_(){}
            
            template<typename ArraySingleDim, std::size_t... Indices>
            constexpr array_impl(ArraySingleDim& data, mk2::container::detail::index_tuple<Indices...>) :
            elems_{data[Indices]...}{}
            
            
            //random_access_iterator_tag
            template<class InputIterator, std::size_t... Indices>
            constexpr array_impl(std::random_access_iterator_tag, InputIterator first, mk2::container::detail::index_tuple<Indices...>)
            : elems_{first[Indices]...}
            {}
            
            //input_iterator_tag
            template<class InputIterator, std::size_t... Indices>
            constexpr array_impl(std::input_iterator_tag, InputIterator first, mk2::container::detail::index_tuple<Indices...>)
            : elems_{(void(Indices), *first++)...}{}
            
            T elems_[Size > 0 ? Size : 1];
        };
    }
    
    template<class T, std::size_t Size>
    class array : private detail::array_impl<T, Size>
    {
        using base = detail::array_impl<T, Size>;
        
    public:
        typedef T                                           value_type;
        typedef value_type&                                 reference;
        typedef const value_type&                           const_reference;
        typedef mk2::iterator::index_iterator<array>        iterator;
        typedef mk2::iterator::index_iterator<const array>  const_iterator;
        typedef value_type*                                 pointer;
        typedef const value_type*                           const_pointer;
        typedef std::size_t                                 size_type;
        typedef std::ptrdiff_t                              difference_type;
        typedef std::reverse_iterator<iterator>             reverse_iterator;
        typedef std::reverse_iterator<const_iterator>       const_reverse_iterator;
        
        constexpr array() : detail::array_impl<T, Size>() {}
        
        constexpr array(const value_type (&v)[Size])
        : detail::array_impl<T, Size>{v, typename mk2::container::index_range<0, Size>::type()} {}
        
        template<class InputIterator>
        constexpr array(InputIterator first, InputIterator last)
        : detail::array_impl<T, Size>{
            typename std::iterator_traits<InputIterator>::iterator_category(),
            first,
            typename mk2::container::index_range<0, Size>::type()
        }{}
        
        constexpr iterator begin() noexcept {return iterator(*this);}
        constexpr const_iterator begin() const noexcept {return const_iterator(*this);}
        
        constexpr iterator end() noexcept {return iterator(*this, Size);}
        constexpr const_iterator end() const noexcept {return const_iterator(*this, Size);}
        
        constexpr reverse_iterator rbegin() noexcept {return reverse_iterator(end());}
        constexpr const_reverse_iterator rbegin() const noexcept {return const_reverse_iterator(end());}
        
        constexpr reverse_iterator rend() noexcept {return reverse_iterator(begin());}
        constexpr const_reverse_iterator rend() const noexcept {return const_reverse_iterator(begin());}
        
        constexpr const_iterator cbegin() const noexcept {return begin();}
        constexpr const_iterator cend() const noexcept {return end();}
        
        constexpr const_reverse_iterator crbegin() const noexcept {return rbegin();}
        constexpr const_reverse_iterator crend() const noexcept {return rend();}
        
        constexpr size_type size() const noexcept {return Size;}
        constexpr size_type max_size() const noexcept {return Size;}
        constexpr bool empty() const noexcept {return Size == 0;}
        
        constexpr reference operator[](size_type n) noexcept {return base::elems_[n];}
        constexpr const_reference operator[](size_type n) const noexcept {return base::elems_[n];}
        
        constexpr reference at(size_type n)
        {
            return n < Size ? base::elems_[n] : throw std::out_of_range("array::at");
        }
        constexpr const_reference at(size_type n) const
        {
            return n < Size ? base::elems_[n] : throw std::out_of_range("array::at");
        }
        
        constexpr reference front() noexcept {return base::elems_[0];}
        constexpr const_reference front() const noexcept {return base::elems_[0];}
        
        constexpr reference back() noexcept {return base::elems_[Size > 0 ? Size-1 : 0];}
        constexpr const_reference back() const noexcept {return base::elems_[Size > 0 ? Size-1 : 0];}
        
        constexpr value_type* data() noexcept {return base::elems_;}
        constexpr value_type* data() const noexcept {return base::elems_;}
    };
    
}
}

