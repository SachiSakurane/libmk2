//
// Created by Himatya on 2018/02/15.
//

#pragma once

#include <type_traits>
#include <iterator>

namespace mk2{
namespace iterator{
    
    namespace detail{
        template<class InputIterator, class Distance>
        inline constexpr void advance_impl(InputIterator& iter, Distance n, std::input_iterator_tag)
        {
            static_assert(n >= 0, "negative value is not allowed");
            for(; n > 0; --n) ++iter;
        }
        
        template<class InputIterator, class Distance>
        inline constexpr void advance_impl(InputIterator& iter, Distance n, std::bidirectional_iterator_tag)
        {
            if(n > 0)
                for(; n > 0; --n) ++iter;
            else
                for(; n < 0; ++n) --iter;
        }
        
        template<class InputIterator, class Distance>
        inline constexpr void advance_impl(InputIterator& iter, Distance n, std::random_access_iterator_tag)
        {
            iter += n;
        }
    }

    template<class InputIterator, class Distance>
    inline constexpr void advance(InputIterator& iter, Distance n)
    {
        return mk2::iterator::detail::advance_impl(iter, n, typename std::iterator_traits<InputIterator>::iterator_category());
    }
}
}
