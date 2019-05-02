//
// Created by Himatya on 2018-10-31.
//

#pragma once

namespace mk2 { namespace simd { namespace intrin {
    template<bool B> struct is_aligned
    {
        static constexpr bool value = B;
    };

    using aligned       = is_aligned<true>;
    using not_aligned   = is_aligned<false>;
}}}