//
//  value_transform_iterator.hpp
//
//
//  Created by Himatya on 2017/01/30.
//  Copyright © 2017年 Himatya. All rights reserved.
//

#pragma once

#include <cstddef>
#include <iterator>
#include <type_traits>

#include <mk2/iterator/type_traits/has_iterator_tag.hpp>

//値が参照された時点でUnaryFunction(x)に変換するイテレータ

namespace mk2{
namespace iterator{

    template<
        class InputIterator, class UnaryFunction,
        typename = typename std::enable_if<mk2::iterator::has_input_iterator_tag<InputIterator>::value>::type
    >
    class value_transform_iterator : public InputIterator
    {
        using base = InputIterator;
        UnaryFunction f;
        
    public:
        using iterator_category = typename base::iterator_category;
        using value_type        = typename base::value_type;
        using difference_type   = typename base::difference_type;
        using pointer           = typename base::pointer;
        using reference         = typename base::reference;
        
        constexpr value_transform_iterator(InputIterator i, UnaryFunction f) noexcept : base(i), f(f){}
        
        constexpr auto operator *()
        {
            return f(base::operator*());
        }
        
        constexpr auto operator *() const
        {
            return f(base::operator*());
        }
        
        constexpr auto operator ->()
        {
            return f(base::operator->());
        }
        
        constexpr auto operator ->() const
        {
            return f(base::operator->());
        }
        
        constexpr auto operator[](typename base::difference_type rhv) 
        {
            return f(base::operator[](rhv));
        }
        
        constexpr auto operator[](typename base::difference_type rhv) const
        {
            return f(base::operator[](rhv));
        }
    };

}
}
