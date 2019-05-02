//
//  pow.hpp
//
//
//  Created by Himatya on 2016/11/20.
//
//

#pragma once

#include <type_traits>
#include <stdexcept>

#include <mk2/math/exp.hpp>
#include <mk2/math/log.hpp>

namespace mk2{
namespace math{
    
    struct magic_number_pow{};
    
    namespace detail{
        
        template<typename T>
        inline constexpr int pow_magic_num(){
            return 0;
        }
        
        template<>
        inline constexpr int pow_magic_num<float>(){
            return 1065307417;
        }
        
        template<>
        inline constexpr int pow_magic_num<double>(){
            return 1072632447;
        }
    }
    
    //http://martin.ankerl.com/2012/01/25/optimized-approximative-pow-in-c-and-cpp/
    template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    [[deprecated("error margin of 5% to 12%, in extreme cases sometimes up to 25%")]]
    inline constexpr T pow(const T a, const T b, magic_number_pow){
        int e = (int)b;
        union{
            T d;
            int x[2];
        } u = { a };
        u.x[1] = (int)((b - e) * (u.x[1] - detail::pow_magic_num<T>()) + detail::pow_magic_num<T>());
        u.x[0] = 0;
        
        double f = a;
        double r = 1.0;
        while(e) {
            if (e & 1) {
                r *= f;
            }
            f *= f;
            e >>= 1;
        }
        
        return r * u.d;
    }
    
    //integral
    template<typename T, typename U, typename = typename std::enable_if<std::is_arithmetic<T>::value && std::is_integral<U>::value>::type>
    inline constexpr T pow(T a, U b){
        T result = static_cast<T>(1.0);
        while(b){
            if(b % 2){
                result *= a;
            }
            a *= a;
            b >>= 1;
        }
        return result;
    }
    
    template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T pow(T a, T b){
        return a > 0 ? mk2::math::exp(b * mk2::math::log(a)) : throw std::range_error("A negative value was specified for the first argument.");
    }
}
}
