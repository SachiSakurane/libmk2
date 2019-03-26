//
//  sampler.hpp
//
//
//  Created by Himatya on 2017/02/01.
//  Copyright © 2017年 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

#include <mk2/container/array.hpp>

namespace mk2{
namespace range{
    namespace detail{
        template<class Function, std::size_t Size>
        class sampler_iterator
        {
        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type        = typename std::invoke_result_t<Function, size_t, const size_t>;
            using difference_type   = std::size_t;
            using pointer           = value_type*;
            using reference         = value_type&;
            
            constexpr sampler_iterator(Function f) noexcept : f_(f){}
            
            constexpr auto operator[](std::size_t index)
            {
                return f_(index, Size);
            }
            
            constexpr auto operator[](std::size_t index) const
            {
                return f_(index, Size);
            }
            
        private:
            Function f_;
        };
        
        template<class Function, std::size_t Size>
        class sampler_holder
        {
            using iterator = sampler_iterator<Function, Size>;
            using value_type = typename std::invoke_result_t<Function, size_t, size_t>;
            
            mk2::container::array<value_type, Size> holder_;
            
        public:
            constexpr sampler_holder(Function f) noexcept : holder_(iterator(f), iterator(f)) {}
            
            constexpr const mk2::container::array<value_type, Size>& container() const { return holder_;}
            
        };
    }
    
    //Function -> type (std::size_t x, const std::size_t size)
    template<std::size_t Size, typename Function>
    inline constexpr auto sampler(Function func){
        return detail::sampler_holder<Function, Size>(func).container();
    }
    
}
}

