//
// Created by Himatya on 2018-11-04.
//

#pragma once

#include <cstddef>

namespace mk2{ namespace utility{

    template <std::size_t Priority>
    struct overload_priority : overload_priority <Priority - 1> {};

    template<>
    struct overload_priority<0> {};

}}