//
// Created by Himatya on 2018/06/13.
//

#pragma once

namespace mk2 {
namespace container {
    template<class Container>
    struct container_traits
    {
        using reference                 = typename Container::reference;
        using const_reference           = typename Container::const_reference;
        using iterator                  = typename Container::iterator;
        using const_iterator            = typename Container::const_iterator;
        using size_type                 = typename Container::size_type;
        using difference_type           = typename Container::difference_type;
        using value_type                = typename Container::value_type;
        using allocator_type            = typename Container::allocator_type;
        using pointer                   = typename Container::pointer;
        using const_pointer             = typename Container::const_pointer;
        using reverse_iterator          = typename Container::reverse_iterator;
        using const_reverse_iterator    = typename Container::const_reverse_iterator;
    };
}
}