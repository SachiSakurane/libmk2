//
// Created by Himatya on 2019-07-21.
//

#pragma once

#include <utility>

namespace mk2 {
namespace utility {

    namespace detail
    {
        constexpr void func_unpack_impl() {}

        template <class Front, class... Args>
        constexpr void func_unpack_impl(Front&& front, Args&&... args)
        {
            std::forward<Front>(front)();
            func_unpack_impl(std::forward<Args>(args)...);
        }
    }

    template <class... Args>
    constexpr void func_unpack(Args&&... args)
    {
        mk2::utility::detail::func_unpack_impl(std::forward<Args>(args)...);
    }
}
}