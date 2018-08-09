//
// Created by Himatya on 2018/08/08.
//

#pragma once

#include <xtensor/xmath.hpp>
#include <xtensor/xview.hpp>

#include <mk2/container/container_traits.hpp>

namespace mk2 { namespace simd { namespace xsimd {
    
    template<class Src, class Dest>
    void auto_correlation(const Src& src, Dest& dest)
    {
        auto value_type = mk2::container::container_traits<Dest>::value_type;
        auto lags_num = dest.size();
        auto size = src.size();
        
        dest.fill(static_cast<value_type>(0));
        
        for (int l = 0; l < lags_num; ++l)
        {
            auto x1 = xt::view(src, xt::range(0, size - l));
            auto x2 = xt::view(src, xt::range(l, size - l));
            dest[l] = xt::sum(x1 * x2)();
        }
    }

}
}
}