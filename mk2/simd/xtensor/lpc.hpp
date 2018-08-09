//
// Created by Himatya on 2018/08/08.
//

#pragma once

#include <xtensor/xbuilder.hpp>

#include <mk2/simd/xtensor/auto_correlation.hpp>
#include <mk2/container/container_traits.hpp>

namespace mk2 { namespace simd { namespace xsimd {
    
    template<class Container>
    class lpc
    {
        using value_type = mk2::container::container_traits<Container>::value_type;
        
    public:
        lpc(int order, int size) : order_(order), lags_num_(order + 1), size_(size),
            r_(xt::empty<value_type>(lags_num_)),
            buffer_(xt::empty<value_type>(size)),
            a_(xt::empty<value_type>(lags_num_)),
            e_(xt::empty<value_type>(lags_num_)),
            U_(xt::empty<value_type>(order + 2)),
            V_(xt::empty<value_type>(order + 2))
        {
        
        }
    
        template<class InputContainer, class OutputContainer>
        void process(const InputContainer& src, OutputContainer& dest)
        {
            auto_correlation(src, r_);
            
            a_.fill(static_cast<value_type>(0));
            e_.fill(static_cast<value_type>(0));
            a_[0] = e_[0] = static_cast<value_type>(1);
            a_[1] = - r_[1] / r_[0];
            e_[1] = r_[0] + r_[1] * a_[1];
            
            xt::flip(r_, r_.size());
            
            for (int k = 1; k < order; ++k)
            {
                value_type lambda(xt::sum() / e_[k]);
            }
    
        }
    private:
        Container r_;
        Container buffer_;
        Container result_;
        Container a_;
        Container e_;
        Container U_;
        Container V_;
    };
    
}
}
}