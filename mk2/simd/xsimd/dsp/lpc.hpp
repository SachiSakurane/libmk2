//
// Created by Himatya on 2018/08/07.
//

#pragma once

#include <type_traits>

#include <boost/simd/algorithm/fill.hpp>
#include <boost/simd/include/functions/sum.hpp>
#include <boost/simd/include/functions/multiplies.hpp>

#include <mk2/container/fixed_array.hpp>
#include <mk2/container/container_traits.hpp>
#include <mk2/simd/xsimd/simd_container.hpp>

namespace mk2 { namespace simd{ namespace xsimd{

    template<
        class Type,
        class Container = mk2::simd::simd_container<Type, mk2::container::fixed_array>,
        typename = typename std::enable_if<
            std::is_same<
                Type,
                mk2::container::container_traits<Container>::value_type
            >::value
        >::type
    >
    class lpc
    {
    public:
        lpc (int order, int size) :
            order_(order), lags_num_(order + 1), size_(size),
            r_(lags_num_),
            buffer_(size),
            a_(lags_num_),
            e_(lags_num_),
            U_(order + 2),
            K_(order + 2)
        {}
        
        template<
            class InputContainer,
            typename = typename std::enable_if<
                std::is_same<
                    Type,
                    mk2::container::container_traits<InputContainer>::value_type
                >::value
            >::type
        >
        const Container& process(const InputContainer& sample)
        {
            namespace bs = boost::simd;
            typedef boost::simd::pack<Type> pack_t;
            
            bs::fill(r_.data(), r_.data() + r_.size(), 0.f);
            bs::fill(buffer_.data(), buffer_.data() + buffer_.size(), 0.f);
            
            for (auto it = std::begin(r_); it != std::end(r_); it != pack_t::static_size)
            {
                buffer_ =
                item = bs::sum();
            }
            
        }
    
    private:
        const int order_;
        const int lags_num_;
        const int size_;
    
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