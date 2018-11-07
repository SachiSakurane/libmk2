//
// Created by Himatya on 2018-11-07.
//

#pragma once

#include <mk2/simd/intrin/include.hpp>

#ifdef __MMX__
#   define MK2_ARCHTECTURE_REQUIREMENT_MMX(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_MMX(x) 
#endif

#ifdef __SSE__
#   define MK2_ARCHTECTURE_REQUIREMENT_SSE(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_SSE(x) 
#endif

#ifdef __SSE2__
#   define MK2_ARCHTECTURE_REQUIREMENT_SSE2(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_SSE2(x) 
#endif

#ifdef __SSE3__
#   define MK2_ARCHTECTURE_REQUIREMENT_SSE3(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_SSE3(x) 
#endif

#ifdef __SSSE3__
#   define MK2_ARCHTECTURE_REQUIREMENT_SSSE3(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_SSSE3(x) 
#endif

#ifdef __SSE4_1__
#   define MK2_ARCHTECTURE_REQUIREMENT_SSE4_1(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_SSE4_1(x) 
#endif

#ifdef __SSE4_2__
#   define MK2_ARCHTECTURE_REQUIREMENT_SSE4_2(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_SSE4_2(x) 
#endif

#ifdef __AES__
#   define MK2_ARCHTECTURE_REQUIREMENT_AES(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_AES(x) 
#endif

#ifdef __AVX__
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX(x) 
#endif

#ifdef __AVX2__
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX2(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX2(x) 
#endif

#ifdef __FMA__
#   define MK2_ARCHTECTURE_REQUIREMENT_FMA(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_FMA(x) 
#endif

#ifdef __AVX512F__
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX512F(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX512F(x) 
#endif

#ifdef __AVX512ER__
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX512ER(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX512ER(x) 
#endif

#ifdef __AVX512CD__
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX512CD(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX512CD(x) 
#endif

#ifdef __AVX512PF__
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX512PF(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX512PF(x) 
#endif

#ifdef __AVX512DQ__
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX512DQ(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX512DQ(x) 
#endif

#ifdef __AVX512BW__
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX512BW(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX512BW(x) 
#endif

#ifdef __AVX512VL__
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX512VL(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX512VL(x) 
#endif

#ifdef __AVX512IFMA__
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX512IFMA(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX512IFMA(x) 
#endif

#ifdef __AVX512VBMI__
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX512VBMI(x) x
#else 
#   define MK2_ARCHTECTURE_REQUIREMENT_AVX512VBMI(x) 
#endif