//
// Created by Himatya on 2018/08/12.
//

#pragma once

#include <mk2/container/fixed_array.hpp>
#include <mk2/math/constants.hpp>
#include <mk2/simd/ipp/function/1d/initialization.hpp>
#include <mk2/simd/ipp/function/1d/statistical.hpp>

namespace mk2 { namespace simd { namespace ipp
{
    template<class Type>
    class lpc
    {
        using complex_type =  mk2::simd::ipp::ipps_complex<Type>;
        template<class ElementType>
        using array_type = mk2::container::fixed_array<ElementType>;
        
    public:
        lpc(int order, int size) : 
            order_(order), delay_(order + 1), size_(size),
            r_(delay_),
            a_(delay_), e_(delay_),
            U_(delay_ + 1), V_(delay_ + 1),
            numerator_(size_), denominator_(size_),
            z_(size_, array_type(order_))
        {
            assert(order > 0);
            // z (0, -2 * pi * 0...n / size)
            // filp( exp(z) )
            array_type<complex_type> num{order_, static_cast<complex_type>(0)};
            for (int i = 0; i < order_; ++i)
                num[i] = static_cast<complex_type>(i);
    
            function::ipps_zero(z_.data(), static_cast<int>(z_.size()));
            for (int i = 0; i < size_; ++i)
            {
                auto z = std::exp(std::complex<Type>(0.0, -mk2::math::two_pi<Type> * n / size));
                auto ipp_z = complex_type{z.real(), z.imag()};
                function::ipps_set(ipp_z, z_[i].data(), order_);
                function::ipps_pow<function::precision_high<Type>>(z_[i].data(), num.data(), order_);
                function::ipps_flip(z_[i].data(), order_);
            }
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
            function::ipps_zero(numerator_.data(), static_cast<int>(numerator_.size()));
            function::ipps_zero(denominator_.data(), static_cast<int>(denominator_.size()));
            
            for (int i = 0; i < size_; ++i)
            {   
                function::ipps_dot_prod(e_.data() - n, z_.data(), numerator_.data() + i, static_cast<int>(e_.size()));
                function::ipps_dot_prod(a_.data() - n, z_.data(), denominator_.data() + i, static_cast<int>(a_.size()));
            }
            
            function::ipps_div_inplace(numerator_.data(), denominator_.data(), size_);
            function::ipps_abs<function::precision_high<Type>>(denominator_.data(), dst, size_);
        }

    private:
        const int order_;
        const int delay_;
        const int size_;
        array_type<Type> r_;
        array_type<Type> a_, e_;
        array_type<Type> U_, V_;
        array_type<complex_type> numerator_, denominator_;
        array_type<array_type<complex_type>> z_;
    };
}
}
}