//
// Created by Himatya on 2018-12-22.
//

#pragma once

#include <mk2/simd/ipp/type.hpp>
#include <mk2/simd/ipp/function/filtering.hpp>

namespace mk2 { namespace simd { namespace ipp {

    template<class Type>
    class fir
    {
    public:
        fir(int size) : size_(size)
        {
            ippsFIRSRGetSize(size_, ipp32f);
        }

    private:
        const int size_;
    };

}}}