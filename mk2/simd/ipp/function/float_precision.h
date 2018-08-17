//
// Created by Himatya on 2018/08/17.
//

#pragma once

#include <type_traits>

#include <ipps.h>

namespace mk2 { namespace simd { namespace ipp { namespace function {
    template<
        class FloatType, std::size_t Size,
        typename = typename std::enable_if<std::is_floating_point<FloatType>::value>::type>
    struct float_precision
    {
        using type = FloatType;
        static size_t size = Size;
    };
    
    template<class FloatType, typename = typename std::enable_if<std::is_floating_point<FloatType>::value>::type>
    struct precision_high;
    
    template<>
    struct precision_high<Ipp32f> : public float_precision<Ipp32f, 24>{};
    
    template<>
    struct precision_high<Ipp64f> : public float_precision<Ipp64f, 53>{};
    
    template<class FloatType, typename = typename std::enable_if<std::is_floating_point<FloatType>::value>::type>
    struct precision_mid;
    
    template<>
    struct precision_mid<Ipp32f> : public precision_mid<Ipp32f, 21>{};
    
    template<>
    struct precision_mid<Ipp64f> : public precision_mid<Ipp64f, 50>{};
    
    template<class FloatType, typename = typename std::enable_if<std::is_floating_point<FloatType>::value>::type>
    struct precision_low;
    
    template<>
    struct precision_low<Ipp32f> : public precision_low<Ipp32f, 11>{};
    
    template<>
    struct precision_low<Ipp64f> : public precision_low<Ipp64f, 26>{};
}}}}