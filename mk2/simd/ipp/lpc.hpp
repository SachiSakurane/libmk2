//
// Created by Himatya on 2018/08/12.
//

#pragma once

#include <complex>
#include <cassert>

#include <mk2/container/fixed_array.hpp>
#include <mk2/math/constants.hpp>
#include <mk2/simd/ipp/type.hpp>
#include <mk2/simd/ipp/function/arithmetic.hpp>
#include <mk2/simd/ipp/function/initialization.hpp>
#include <mk2/simd/ipp/function/statistical.hpp>
#include <mk2/simd/ipp/function/conversion.hpp>
#include <mk2/simd/ipp/function/fixed_accuracy_arithmetic.hpp>

namespace mk2 { namespace simd { namespace ipp
{
    template<class Type>
    class lpc
    {
        using complex_type = mk2::simd::ipp::ipps_complex<Type>;
        template<class ElementType>
        using array_type = mk2::container::fixed_array<ElementType>;
        
    public:
        lpc(int order, int size) : 
            order_(order), delay_(order + 1), size_(size),
            r_(delay_),
            a_(delay_), e_(delay_),
            U_(delay_ + 1), V_(delay_ + 1),
            numerator_(size_), denominator_(size_),
            z_(size_, array_type<complex_type>(delay_))
        {
            assert(order > 0);
            
            array_type<complex_type> num(delay_);
            for (int i = 0; i < delay_; ++i)
                num[i] = complex_type{static_cast<Type>(i), static_cast<Type>(0)};
            
            for (int i = 0; i < size_; ++i)
            {
                auto z = std::exp(std::complex<Type>(0.0, -mk2::math::two_pi<Type> * i / size_));
                auto ipp_z = complex_type{z.real(), z.imag()};
                function::set(ipp_z, z_[i].data(), static_cast<int>(z_[i].size()));
                function::pow(z_[i].data(), num.data(), z_[i].data(), static_cast<int>(z_[i].size()), function::precision_high{});
                function::flip_inplace(z_[i].data(), static_cast<int>(z_[i].size()));
            }
        }

        void operator()(const Type* src, Type* dst)
        {
            for (int l = 0; l < delay_; ++l)
            {
                function::dot_prod(src, src + l, static_cast<int>(size_ - l), r_.data() + l);
            }
            
            function::flip_inplace(r_.data(), static_cast<int>(r_.size()));
            auto r_back = r_.size() - 1;
            
            function::zero(a_.data(), static_cast<int>(a_.size()));
            function::zero(e_.data(), static_cast<int>(e_.size()));
            
            a_[0] = e_[0] = static_cast<Type>(1);
            a_[1] = - r_[r_back - 1] / r_[r_back];
            e_[1] = r_[r_back] + r_[r_back - 1] * a_[1];
            
            function::zero(U_.data(), static_cast<int>(U_.size()));
            U_[0] = static_cast<Type>(1);
            
            for (int i = 1; i < order_; ++i)
            {
                Type lambda = static_cast<Type>(0);
    
                function::dot_prod(a_.data(), r_.data() + (r_back - i - 1), i + 1, &lambda);
                lambda /= -e_[i];
                
                function::copy(a_.data() + 1, U_.data() + 1, i);
                function::flip(U_.data(), V_.data(), i + 2);
    
                function::mulc_inplace(lambda, V_.data(), i + 2);
                function::add(U_.data(), V_.data(), a_.data(), i + 2);
    
                e_[i + 1] = e_[i] * (static_cast<Type>(1) - lambda * lambda);
            }
            
            // filter
            function::zero(numerator_.data(), static_cast<int>(numerator_.size()));
            function::zero(denominator_.data(), static_cast<int>(denominator_.size()));
            
            for (int i = 0; i < size_; ++i)
            {   
                function::dot_prod(e_.data(), z_[i].data(), static_cast<int>(e_.size()), numerator_.data() + i);
                function::dot_prod(a_.data(), z_[i].data(), static_cast<int>(a_.size()), denominator_.data() + i);
            }
            
            function::div_inplace(denominator_.data(), numerator_.data(), size_);
            function::abs(numerator_.data(), dst, size_, function::precision_high{});
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