//
//  end.hpp
//
//
//  Created by Himatya on 2017/01/29.
//  Copyright © 2017年 Himatya. All rights reserved.
//

#pragma once

namespace mk2{
namespace iterator{
    
    template<class T>
    inline constexpr auto end(T& v) -> decltype(v.end())
    {
        return v.end();
    }
    
    template<class T>
    inline constexpr auto rend(T& v) -> decltype(v.rend())
    {
        return v.rend();
    }
    
    template<class T>
    inline constexpr auto cend(T& v) -> decltype(v.cend())
    {
        return v.cend();
    }
    
    template<class T>
    inline constexpr auto crend(T& v) -> decltype(v.crend())
    {
        return v.crend();
    }
    
    template<class T>
    inline constexpr auto end(const T& v) -> decltype(v.end())
    {
        return v.end();
    }
    
    template<class T>
    inline constexpr auto rend(const T& v) -> decltype(v.rend())
    {
        return v.rend();
    }
    
    template<class T>
    inline constexpr auto cend(const T& v) -> decltype(v.cend())
    {
        return v.cend();
    }
    
    template<class T>
    inline constexpr auto crend(const T& v) -> decltype(v.crend())
    {
        return v.crend();
    }
    
}
}

