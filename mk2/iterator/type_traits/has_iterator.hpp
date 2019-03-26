//
//  has_iterator.hpp
//
//
//  Created by Himatya on 2017/01/30.
//  Copyright © 2017年 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

namespace mk2{
namespace iterator{

    namespace detail{
        struct has_iterator_impl{
            template<class T>
            static constexpr std::true_type check(typename T::iterator*);
        
            template<class T>
            static constexpr std::false_type check(...);
        };
    }
    
    template<class T>
    class has_iterator : public decltype(detail::has_iterator_impl::check<T>(nullptr)){};
    
}
}
