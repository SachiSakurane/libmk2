//
//  has_iterator_tag.hpp
//
//
//  Created by Himatya on 2017/01/30.
//  Copyright © 2017年 Himatya. All rights reserved.
//

#pragma once

#include <iterator>
#include <type_traits>

namespace mk2{
namespace iterator{
    
    #define MAKE_ITERATOR_TAG(tag_name)									\
    namespace detail{													\
	    struct has_##tag_name##_impl{									\
	    	template<class T>											\
	    	static constexpr std::true_type check(std::tag_name *);	\
	    	template<class T>											\
	    	static constexpr std::false_type check(...);				\
	    };																\
    }																	\
    template<class T>													\
    class has_##tag_name :												\
    public decltype(detail::has_##tag_name##_impl::check				\
    <typename std::iterator_traits<T>::iterator_category>(nullptr)){};	\
    
    MAKE_ITERATOR_TAG(input_iterator_tag)
    MAKE_ITERATOR_TAG(output_iterator_tag)
    MAKE_ITERATOR_TAG(forward_iterator_tag)
    MAKE_ITERATOR_TAG(bidirectional_iterator_tag)
    MAKE_ITERATOR_TAG(random_access_iterator_tag)
    
    #undef MAKE_ITERATOR_TAG
    
}
}
