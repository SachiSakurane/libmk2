//
//  asin.hpp
//
//
//  Created by Himatya on 2017/02/07.
//  Copyright (c) 2017 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>
#include <limits>

#include <mk2/math/constants.hpp>
#include <mk2/math/pow.hpp>
#include <mk2/math/sqrt.hpp>

//1 < |x| return NaN

//https://opensource.apple.com/source/Libm/Libm-2026/Source/Intel/
//https://opensource.apple.com/source/Libm/Libm-2026/Source/Intel/asin.c

namespace mk2{
namespace math{
    namespace detail{
    
        //0.5 < x <= 1
        template<class T>
        inline constexpr T asin_tail(T x){
            if(1 <= x)
                return 1 == x
                    ? mk2::math::half_pi<T>
                    : std::numeric_limits<T>::quiet_NaN();
            return mk2::math::half_pi<T> + mk2::math::sqrt(1-x) * (((( (((( (((( (
                + -0.0000121189820098929624806) * x
                +  0.0001307564187657962919394) * x
                + -0.0006702485124770180942917) * x
                +  0.0021912255981979442677477) * x
                
                + -0.0052049731575223952626203) * x
                +  0.0097868293573384001221447) * x
                + -0.0156746038587246716524035) * x
                +  0.0229883479552557203133368) * x
                
                + -0.0331919619444009606270380) * x
                +  0.0506659694457588602631748) * x
                + -0.0890259194305537131666744) * x
                +  0.2145993335526539017488949) * x
                
                + -1.5707961988153774692344105L);
        }
        
        //|x| <= 5
        template<class T>
        inline constexpr T asin_center(T x){
            if(-0x1.7137449123ef5p-26 <= x && x <= +0x1.7137449123ef5p-26)
                return -0x1p-1022 < x && x < +0x1p-1022
                    ? x - x * x
                    : x * (0x1p-1022 + 1);
            double x2 = x * x;
            return (((( (((( ((((
                +  0.0316658385792867081040808) * x2
                + -0.0158620440988475212803145) * x2
                +  0.0192942786775238654913582) * x2
                +  0.0066153165197009078340075) * x2
                
                +  0.0121483892822292648695383) * x2
                +  0.0138885410156894774969889) * x2
                +  0.0173593516996479249428647) * x2
                +  0.0223717830666671020710108) * x2
                
                +  0.0303819580081956423799529) * x2
                +  0.0446428568582815922683933) * x2
                +  0.0750000000029696112392353) * x2
                +  0.1666666666666558995379880) * x2 * x + x;
        }
    
        template<class T>
        inline constexpr T asin_impl(T x){
            if(x < -.5)
                return -mk2::math::detail::asin_tail(-x);
            else if(x <= .5)
                return mk2::math::detail::asin_center(x);
            return mk2::math::detail::asin_tail(x);
        }
    }
    
    template<class T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T asin(T x){
        return math::detail::asin_impl(x);
    }
}
}