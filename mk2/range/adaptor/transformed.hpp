//
//  transformed.hpp
//
//
//  Created by Himatya on 2017/01/30.
//  Copyright © 2017年 Himatya. All rights reserved.
//

#pragma once

#include <utility>

#include <mk2/iterator/begin.hpp>
#include <mk2/iterator/end.hpp>
#include <mk2/iterator/value_transform_iterator.hpp>

//transform_iteratorでなんとかできそう

namespace mk2{
namespace range{
    namespace adaptors{
        
        template<class UnaryFunction>
        class transform_tag
        {
        public:
            constexpr transform_tag(UnaryFunction f) noexcept : f_(f){}
            
            template<class T>
            constexpr auto operator()(T&& arg) -> decltype(f_(std::forward<T>(arg)))
            {
                return f_(std::forward<T>(arg));
            }
            
            template<class T>
            constexpr auto operator()(T&& arg) const -> decltype(f_(std::forward<T>(arg)))
            {
                return f_(std::forward<T>(arg));
            }
            
        private:
            UnaryFunction f_;
        };
        
        template<class Range, class UnaryFunction>
        inline constexpr decltype(auto) operator| (const Range& r, transform_tag<UnaryFunction> func)
        {
            using value_transform_iterator = typename mk2::iterator::value_transform_iterator<typename Range::iterator, transform_tag<UnaryFunction>>;
            return Range(value_transform_iterator(mk2::iterator::cbegin(r), func),
                         value_transform_iterator(mk2::iterator::cend(r), func));
        }
        
        template<class Range, class UnaryFunction>
        inline constexpr decltype(auto) operator| (Range& r, transform_tag<UnaryFunction> func)
        {
            using value_transform_iterator = typename mk2::iterator::value_transform_iterator<typename Range::iterator, transform_tag<UnaryFunction>>;
            return Range(value_transform_iterator(mk2::iterator::begin(r), func),
                         value_transform_iterator(mk2::iterator::end(r), func));
        }
        
        template<class UnaryFunction>
        inline constexpr transform_tag<UnaryFunction> transformed(UnaryFunction func)
        {
            return transform_tag<UnaryFunction>(func);
        }
    }
}
}

