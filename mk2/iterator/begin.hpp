//
//  begin.hpp
//
//
//  Created by Himatya on 2017/01/28.
//  Copyright © 2017年 Himatya. All rights reserved.
//

#pragma once

namespace mk2{
namespace iterator{
    
    template<class T>
    inline constexpr auto begin(T& v) -> decltype(v.begin())
    {
        return v.begin();
    }
    
    template<class T>
    inline constexpr auto rbegin(T& v) -> decltype(v.rbegin())
    {
        return v.rbegin();
    }
    
    template<class T>
    inline constexpr auto cbegin(T& v) -> decltype(v.cbegin())
    {
        return v.cbegin();
    }
    
    template<class T>
    inline constexpr auto crbegin(T& v) -> decltype(v.crbegin())
    {
        return v.crbegin();
    }
    
    template<class T>
    inline constexpr auto begin(const T& v) -> decltype(v.begin())
    {
        return v.begin();
    }
    
    template<class T>
    inline constexpr auto rbegin(const T& v) -> decltype(v.rbegin())
    {
        return v.rbegin();
    }
    
    template<class T>
    inline constexpr auto cbegin(const T& v) -> decltype(v.cbegin())
    {
        return v.cbegin();
    }
    
    template<class T>
    inline constexpr auto crbegin(const T& v) -> decltype(v.crbegin())
    {
        return v.crbegin();
    }
    
}
}

