//
// Created by Himatya on 2018-12-03.
//

#pragma once

#include <mk2/simd/ipp/function/arithmetic.hpp>

namespace mk2 { namespace simd { namespace ipp
{
    template <class Type>
    IppStatus scaling(const Type* src, Type* dst, Type src_min, Type src_max, Type dst_min, Type dst_max, int len)
    {
        IppStatus err = ippStsNoErr;

        auto dur = src_max - src_min;

        err |= mk2::simd::ipp::function::mulc(src, (dst_max - dst_min) / dur, dst, len);
        err |= mk2::simd::ipp::function::addc_inplace((src_max * dst_min - src_min * dst_max) / dur, dst, len);

        return err;
    }

    template <class Type>
    IppStatus scaling_inplace(Type* src_dst, Type src_min, Type src_max, Type dst_min, Type dst_max, int len)
    {
        IppStatus err = ippStsNoErr;

        auto dur = src_max - src_min;

        err |= mk2::simd::ipp::function::mulc_inplace((dst_max - dst_min) / dur, src_dst, len);
        err |= mk2::simd::ipp::function::addc_inplace((src_max * dst_min - src_min * dst_max) / dur, src_dst, len);

        return err;
    }
}}}