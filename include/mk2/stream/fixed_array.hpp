//
// Created by Himatya on 2018/01/25.
//

#ifndef LIBMK2_STREAM_FIXED_ARRAY_HPP
#define LIBMK2_STREAM_FIXED_ARRAY_HPP

#include <ostream>

#include <mk2/container/fixed_array.hpp>

namespace mk2 { 
namespace container{
    template<typename Type, typename Allocator>
    std::ostream &operator<<(std::ostream &ost, const fixed_array<Type, Allocator> &c) {
        for (auto &&item : c) {
            ost << item << ",";
        }
        return ost;
    }
    
    template<typename Type, typename Allocator>
    std::wostream &operator<<(std::wostream &ost, const fixed_array<Type, Allocator> &c) {
        for (auto &&item : c) {
            ost << item << L",";
        }
        return ost;
    }
}
}

#endif //LIBMK2_STREAM_ARRAY_HPP