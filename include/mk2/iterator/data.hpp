//
// Created by Himatya on 2018/01/31.
//

#ifndef LIBMK2_ITERATOR_DATA_HPP
#define LIBMK2_ITERATOR_DATA_HPP

#include <initializer_list>

namespace mk2{
namespace iterator{
    template<class Container>
    constexpr auto data(Container& c) -> decltype(c.size())
    {
        return c.data();
    }

    template<class Container>
    constexpr auto data(const Container& c) -> decltype(c.size())
    {
        return c.data();
    }
    
    template <class T, std::size_t N>
    constexpr std::size_t data(const T (&array)[N]) noexcept
    {
        return array;
    }
    
    template <class E>
    constexpr const E* data(std::initializer_list<E> il) noexcept
    {
        return il.begin();
    }
}
}

#endif