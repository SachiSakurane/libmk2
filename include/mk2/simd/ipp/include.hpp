//
// Created by Himatya on 2019-05-17.
//

#pragma once

#include <ipps.h>

#ifdef _MSC_VER
#   if defined(__SSE3__) && __has_include(<ipp_m7.h>)
#       include <ipp_m7.h>
#   endif
#   if defined(__SSSE3__) && __has_include(<ipp_n8.h>)
#       include <ipp_n8.h>
#   endif
#   if defined(__SSE4_2__) && __has_include(<ipp_y8.h>)
#       include <ipp_y8.h>
#   endif
#   if defined(__AVX__) && __has_include(<ipp_e9.h>)
#       include <ipp_e9.h>
#   endif
#   if defined(__AVX2__) && __has_include(<ipp_l9.h>)
#       include <ipp_l9.h>
#   endif
#   if defined(__AVX512F__) && __has_include(<ipp_n0.h>)
#       include <ipp_n0.h>
#   endif
#   if defined(__AVX512F__) && __has_include(<ipp_k0.h>)
#       include <ipp_k0.h>
#   endif
#endif