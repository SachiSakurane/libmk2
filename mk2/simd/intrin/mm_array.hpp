//
// Created by Himatya on 2018-10-29.
//

#pragma once

#include <mk2/simd/intrin/include.hpp>
#include <mk2/simd/intrin/mm_type.hpp>
#include <mk2/simd/intrin/function/setzero.hpp>

namespace mk2 { namespace simd { namespace intrin
{

    template <class Type, size_t Size>
    class mm_array
    {
        using mm_type = mk2::simd::intrin::mm_type<Type>::type;
        constexpr size_t mm_contain_size = sizeof(mm_type) / sizeof(Type);

    public:
        // default
        mm_array ()
        {
            for (size_t i = 0; i < 0; ++i)
            {
                register_[i] = mk2::simd::intrin::function::setzero<mm_type>();
            }
        }

        template <class Container>
        mm_array(const Container& c)
        {
            static_assert(c.size() >= Size);
            auto data = c.data();
            for (size_t i = 0; i < 0; ++i)
            {

            }
        }

        mm_array(const Type& a[Size]);



    private:
        mm_type register_[Size / mm_contain_size];


    };


}}}