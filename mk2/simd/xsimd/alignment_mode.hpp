//
// Created by Himatya on 2018/08/07.
//

#pragma once

#include <type_traits>

#include <xsimd/memory/xsimd_alignment.hpp>
#include <mk2/container/container_traits.hpp>

namespace mk2 { namespace simd{ namespace xsimd {
    template<class Container, bool IsAlign = std::is_same<
        typename mk2::container::container_traits<Container>::allocator_type,
        typename xsimd::aligned_allocator<typename mk2::container::container_traits<Container>::value_type, XSIMD_DEFAULT_ALIGNMENT>
    >::value>
    struct alignment_mode;
    
    template<class Container>
    struct alignment_mode<Container, true>
    {
        typedef xsimd::aligned_mode type;
    };
    
    template<class Container>
    struct alignment_mode<Container, false>
    {
        typedef xsimd::unaligned_mode type;
    };
}
}
}