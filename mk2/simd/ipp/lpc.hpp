//
// Created by Himatya on 2018/08/12.
//

#pragma once

#include <mk2/container/fixed_array.hpp>
#include <mk2/simd/ipp/function/initialization.hpp>
#include <mk2/simd/ipp/function/statistical.hpp>

namespace mk2 { namespace simd { namespace ipp
{
    template<class Type>
    class lpc
    {
    public:
        lpc(int order) : 
            order_(order), lags_num_(order + 1),
            r_(lags_num_),
            a_(lags_num_), e_(lags_num_),
            a_(lags_num_), e_(lags_num_)
        {
        }

        void process(const Type* src, Type* dst, int len)
        {
            for (int l = 0; l < lags_num; ++l)
            {
                Type dp = 0;
                function::ipps_dot_prod(src, src + l, len - l, dp);
                r_[l] = dp;
            }
            
            
        }

    private:
        const int order_;
        const int lags_num_;
        mk2::container::fixed_array<Type> r_;
        mk2::container::fixed_array<Type> a_, e_;
        mk2::container::fixed_array<Type> U_, V_;
    };
}
}
}