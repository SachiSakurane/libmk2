//
// Created by Himatya on 2018/08/07.
//

#pragma once

#include <type_traits>
#include <iterator>

#include <mk2/simd/xsimd/function/sum.hpp>

//自己相関関数

namespace mk2 { namespace simd{ namespace xsimd{
namespace dsp
{
    
    template<
        class InputContainer,
        class OutputContainer,
        class Type = typename std::iterator_traits<InputContainer>::value_type
    >
    void auto_correlation(const InputContainer& src, OutputIterator& dest)
    {
    
    }
}
}
}
}