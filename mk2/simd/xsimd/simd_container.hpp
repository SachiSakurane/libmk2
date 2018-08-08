//
// Created by Himatya on 2018/08/07.
//

#pragma once

#include <xsimd/config/xsimd_align.hpp>
#include <xsimd/memory/xsimd_aligned_allocator.hpp>

namespace mk2 { namespace simd {
namespace xsimd
{
    template<class Type, template<class, class> Container>
    using simd_container = Container <Type, xsimd::aligned_allocator<Type, XSIMD_DEFAULT_ALIGNMENT>>
}
}
}