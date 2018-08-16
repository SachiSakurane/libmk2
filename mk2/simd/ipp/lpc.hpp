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
        using complex_type =  mk2::simd::ipp::ipps_complex<Type>;
    public:
        lpc(int order, int size) : 
            order_(order), delay_(order + 1), size_(size),
            r_(delay_),
            a_(delay_), e_(delay_),
            U_(delay_ + 1), V_(delay_ + 1),
            z_(size * order_)
        {
            assert(order > 0)
            // z (0, -2 * pi * 0...n / size)
            // filp( exp(z) )
            
        }

        void process(const Type* src, Type* dst)
        {
            for (int l = 0; l < delay_; ++l)
            {
                Type dp = 0;
                function::ipps_dot_prod(src, src + l, len - l, dp);
                r_[l] = dp;
            }
            
            function::ipps_filp_inplace(r_.data(), static_cast<int>(r_.size()));
            auto r_back = r_.size() - 1;
            function::ipps_zero(a_.data(), static_cast<int>(a_.size()));
            function::ipps_zero(e_.data(), static_cast<int>(e_.size()));
            
            a_[0] = e_[0] = static_cast<Type>(1);
            a_[1] = -r_[r_back - 1] * a_[1];
            e_[1] = r_[r_back] + r_[r_back - 1] * a_[1];
            U_[0] = static_cast<Type>(0);
            
            for (int i = 1; i < order_; ++i)
            {
                Type lambda = static_cast<Type>(0);
                
                function::ipps_dot_prod(a_.data(), r_.data() + (r_back - i), i, lambda);
                lambda /= -e_[i];
                
                U_[i + 1] = static_cast<Type>(1);
                function::ipps_copy(a_.data() + 1, U_.data() + 1, i);
                function::ipps_filp(U_.data(), V_.data(), i + 2);
                
                function::ipps_mulc_inplace(lambda, V_.data(), i + 2);
                function::ipps_add(U_.data(), V_.data(), a_.data(), i + 2);
                
                e_[i + 1] = e_[i] * (1.0 - lambda * lambda);
            }
            
            // filter
            //for ()
            //complex_type numerator(static_cast<Type>(0), static_cast<Type>(0));
            //complex_type denominator(static_cast<Type>(0), static_cast<Type>(0));
            
            //function::ipps_dot_prod(e_.data() - n, z_.data(), numerator, static_cast<int>(e_.size()));
            //function::ipps_dot_prod(a_.data(), z_.data(), numerator, static_cast<int>(a_.size()));
            //std::abs(numerator)
        }

    private:
        const int order_;
        const int delay_;
        const int size_;
        mk2::container::fixed_array<Type> r_;
        mk2::container::fixed_array<Type> a_, e_;
        mk2::container::fixed_array<Type> U_, V_;
        mk2::container::fixed_array<complex_type> z_;
        
    };
}
}
}