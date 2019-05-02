//
// Created by Himatya on 2018/01/31.
//

#ifndef LIBMK2_ITERATOR_SIZE_HPP
#define LIBMK2_ITERATOR_SIZE_HPP

namespace mk2{
namespace iterator{
    template<class Container>
    constexpr auto size(const Container& c) -> decltype(c.size())
    {
        return c.size();
    }
    
    template <class T, std::size_t N>
    constexpr std::size_t size(const T (&array)[N]) noexcept
    {
        return N;
    }
}
}

#endif