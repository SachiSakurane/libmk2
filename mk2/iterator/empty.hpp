//
// Created by Himatya on 2018/01/31.
//

#ifndef LIBMK2_ITERATOR_EMPTY_HPP
#define LIBMK2_ITERATOR_EMPTY_HPP

namespace mk2{
namespace iterator{
    template<class Container>
    constexpr auto empty(const Container& c) -> decltype(c.empty())
    {
        return c.empty();
    }
    
    template <class T, std::size_t N>
    constexpr bool empty(const T (&array)[N]) noexcept
    {
        return false;
    }
    
    template <class E>
    constexpr bool empty(initializer_list<E> il) noexcept
    {
        return il.size() == 0;
    }
}
}

#endif