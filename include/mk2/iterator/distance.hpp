//
//  distance.hpp
//
//  Created by Himatya on 2017/01/22.
//  Copyright (c) 2017年 Himatya. All rights reserved.
//

#pragma once

#include <iterator>

namespace mk2{
namespace iterator{
    
    namespace detail{
        template<class InputIterator>
        inline constexpr typename std::iterator_traits<InputIterator>::difference_type
        distance_impl(InputIterator first, InputIterator last, std::input_iterator_tag)
        {
            typename std::iterator_traits<InputIterator>::difference_type distance(0);
            for(; first != last; ++first)
                ++distance;
            return distance;
        }
        
        template<class InputIterator>
        inline constexpr typename std::iterator_traits<InputIterator>::difference_type
        distance_impl(InputIterator first, InputIterator last, std::random_access_iterator_tag)
        {
            return last - first;
        }
    }
    
    template<class InputIterator>
    inline constexpr typename std::iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last)
    {
        return detail::distance_impl(first, last, typename std::iterator_traits<InputIterator>::iterator_category());
    }
}
}
