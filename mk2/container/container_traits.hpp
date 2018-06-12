//
// Created by Himatya on 2018/06/13.
//

#pragma once

namespace mk2 {
namespace container {
    template<class Container>
    struct container_traits
    {
        using value_type        = typename Container::value_type;
        using reference         = typename Container::reference;
        using const_reference   = typename Container::const_reference;
        using iterator          = typename Container::iterator;
        using const_iterator    = typename Container::const_iterator;
        using difference_type   = typename Container::difference_type;
        using size_type         = typename Container::size_type;
    };
}
}