//
//  sampled_trigonometric.hpp
//
//
//  Created by Himatya on 2017/02/05.
//  Copyright © 2017年 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

#include <mk2/math/constants.hpp>
#include <mk2/math/cos.hpp>
#include <mk2/math/lerp.hpp>
#include <mk2/math/theta_mod.hpp>
#include <mk2/range/sampler.hpp>

namespace mk2{
namespace math{
    namespace detail{
        template<typename T>
        inline constexpr T cos_table(std::size_t x, const std::size_t size){
            return mk2::math::cos<T>(mk2::math::two_pi<T> * (static_cast<T>(x) / static_cast<T>(size)));
        }
        
        template<typename T, std::size_t Size>
        struct pi_table{
            static inline constexpr std::size_t size() { return Size; }
            static inline constexpr T round() {return math::pi<T> / static_cast<T>(Size);}
            static inline constexpr T two_pi_par_table() { return math::two_pi<T> / static_cast<T>(Size); }
            static inline constexpr T pi_par_table() { return math::pi<T> / static_cast<T>(Size); }
            static inline constexpr T table_par_two_pi() { return math::inv_two_pi<T> * static_cast<T>(Size); }
            static inline constexpr T table_par_pi() { return math::inv_pi<T> * static_cast<T>(Size); }
        };
        
        template<class T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        constexpr T lagrange_impl(T x, int i, int first, int n, int cnt = 0)
        {
            if(n<=cnt)return static_cast<T>(1);
            T x_j = static_cast<T>(first+cnt);
            return i != x_j
            ? lagrange_impl<T>(x, i, first, n, cnt+1) * (x - x_j) / (static_cast<T>(i) - x_j)
            : lagrange_impl<T>(x, i, first, n, cnt+1);
        }
    }
    
    struct direct_reference{
        template<typename T, typename Ary, typename PI_Table>
        static inline constexpr T interpolation(const Ary& ary, T x, PI_Table){
            return ary[static_cast<std::size_t>(x * PI_Table::table_par_two_pi())];
        }
    };
    
    struct round_reference{
        template<typename T, typename Ary, typename PI_Table>
        static inline constexpr T interpolation(const Ary& ary, T x, PI_Table){
            std::size_t table = static_cast<std::size_t>((x + PI_Table::round()) * PI_Table::table_par_two_pi());
            return ary[table == PI_Table::size() ? 0 : table];
        }
    };
    
    struct linear_interpolation{
        template<typename T, typename Ary, typename PI_Table>
        static inline constexpr T interpolation(const Ary& ary, T x, PI_Table){
            T table_theta = x * PI_Table::table_par_two_pi();
            std::size_t round = static_cast<std::size_t>(table_theta);
            T sub = table_theta - static_cast<T>(round);
            return mk2::math::lerp(ary[round + 1 == PI_Table::size() ? 0 : round + 1], ary[round], sub);
        }
    };
    
    template<std::size_t Size = 3>
    struct lagrange_interpolation{
        template<typename T, typename Ary, typename PI_Table>
        static inline constexpr T interpolation(const Ary& ary, T x, PI_Table){
            T table_theta = x * PI_Table::table_par_two_pi();
            int round = static_cast<int>(table_theta + PI_Table::round());
            int half = Size >> 1;
            int lst = Size - half;
            T sum = 0;
            for(int i = -half; i < lst; ++i){
                T a = ary[(round + i + PI_Table::size()) % PI_Table::size()];
                T b = mk2::math::detail::lagrange_impl(table_theta, round + i, round - half, static_cast<int>(Size));
                sum += a * b;
            }
            return sum;
        }
    };
    
    template<
        typename T,
        std::size_t Size,
        typename = typename std::enable_if<std::is_floating_point<T>::value>::type
    >
    class sampled_trigonometric{
    public:
        constexpr sampled_trigonometric() :
            holder_(mk2::range::sampler<Size>(mk2::math::detail::cos_table<T>)){}
        
        template<
            typename Interpolation,
            typename U,
            typename = typename std::enable_if<std::is_floating_point<U>::value>::type
        >
        inline constexpr T cos(U x) const {
            return Interpolation::interpolation(holder_, mk2::math::theta_mod(x), mk2::math::detail::pi_table<T, Size>());
        }
        
        template<
            typename U,
            typename = typename std::enable_if<std::is_floating_point<U>::value>::type
        >
        inline constexpr T cos(U x) const {
            return cos<round_reference, U>(x);
        }
        
        template<
            typename Interpolation,
            typename U,
            typename = typename std::enable_if<std::is_floating_point<U>::value>::type
        >
        inline constexpr T sin(U x) const {
            return cos<Interpolation, U>(x - mk2::math::half_pi<T>);
        }
        
        template<
            typename U,
            typename = typename std::enable_if<std::is_floating_point<U>::value>::type
        >
        inline constexpr T sin(U x) const {
            return sin<round_reference, U>(x);
        }
        
        template<
            typename Interpolation,
            typename U,
            typename = typename std::enable_if<std::is_floating_point<U>::value>::type
        >
        inline constexpr T tan(U x) const {
            return sin<Interpolation, U>(x) / cos<Interpolation, U>(x);
        }
        
        template<
            typename U,
            typename = typename std::enable_if<std::is_floating_point<U>::value>::type
        >
        inline constexpr T tan(U x) const {
            return tan<round_reference, U>(x);
        }
        
    private:
        mk2::container::array<T, Size> holder_;
    };
}
}
