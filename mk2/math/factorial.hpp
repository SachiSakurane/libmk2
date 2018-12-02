//
//  factorial.hpp
//
//
//  Created by Himatya on 2016/11/20.
//
//

#pragma once

#include <limits>
#include <type_traits>

#include <mk2/container/array.hpp>
#include <mk2/range/sampler.hpp>

namespace mk2{
namespace math{
    namespace detail {
        template<typename T>
        static constexpr const T factorial_impl2(const std::size_t x, const std::size_t size){
            return x == 0 ? static_cast<T>(1) : factorial_impl2<T>(x - 1, size) * x;
        }
        
        template<typename T, std::size_t Size>
        static constexpr const bool is_calcuratable_factorial(){
            return (Size == 0) || (factorial_impl2<T>(Size, Size) <= std::numeric_limits<T>::max() / Size);
        }
        
        template<typename T, std::size_t Size, typename Enable = void>
        struct factorial_impl{};
        
        template<typename T, std::size_t Size>
        struct factorial_impl<
            T,
            Size,
            typename std::enable_if<is_calcuratable_factorial<T, Size>()>::type
        >
        : public factorial_impl<T, Size + 1>{};
        
        template<typename T, std::size_t Size>
        struct factorial_impl<
            T,
            Size,
            typename std::enable_if<!is_calcuratable_factorial<T, Size>()>::type
        >
        {
            typedef T type;
            static constexpr std::size_t size(){return Size;}
            
            constexpr factorial_impl() : table(mk2::range::sampler<Size>(factorial_impl2<T>)){}
            
            mk2::container::array<type, Size> table;
        };
        
        template<typename T>
        static constexpr const mk2::math::detail::factorial_impl<T, 0> factorial_table{};
        
        //inverse
        template<typename T>
        static constexpr const T inverse_factorial_impl2(const std::size_t x, const std::size_t size){
            return static_cast<T>(1) / factorial_impl2<T>(x, size);
        }
        
        template<typename T, std::size_t Size, typename Enable = void>
        struct inverse_factorial_impl{};
        
        template<typename T, std::size_t Size>
        struct inverse_factorial_impl<
            T,
            Size,
            typename std::enable_if<is_calcuratable_factorial<T, Size>()>::type
        >
        : public inverse_factorial_impl<T, Size + 1>{};
        
        template<typename T, std::size_t Size>
            struct inverse_factorial_impl<
            T,
            Size,
            typename std::enable_if<!is_calcuratable_factorial<T, Size>()>::type
        >
        {
            typedef T type;
            static constexpr std::size_t size(){return Size;}
            
            constexpr inverse_factorial_impl() : table(mk2::range::sampler<Size>(inverse_factorial_impl2<T>)){}
            
            mk2::container::array<type, Size> table;
        };
        
        template<typename T>
        static constexpr const mk2::math::detail::inverse_factorial_impl<T, 0> inverse_factorial_table{};
    }
    
    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    static constexpr const T factorial(std::size_t val){
        return mk2::math::detail::factorial_table<T>.table[val];
    }
    
    template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    static constexpr const T inverse_factorial(std::size_t val){
        return mk2::math::detail::inverse_factorial_table<T>.table[val];
    }
}
}
