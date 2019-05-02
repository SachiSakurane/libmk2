//
// Created by Himatya on 2018/02/15.
//

#pragma once

#include <type_traits>

#include <mk2/iterator/advance.hpp>
#include <mk2/iterator/begin.hpp>

namespace mk2{
namespace range{
namespace adaptors{
    
    struct ranged_tag
    {
        constexpr ranged_tag(size_t first, size_t end) : first_(first), end_(end) {}
        
        size_t first_;
        size_t end_;
    };
    
    template<class Range>
    inline constexpr const Range operator| (const Range& r, ranged_tag range)
    {
        return Range(mk2::iterator::advance(mk2::iterator::cbegin(r), range.first_),
                     mk2::iterator::advance(mk2::iterator::cbegin(r), range.end_));
    }
    
    template<class Range>
    inline constexpr Range operator| (Range& r, ranged_tag range)
    {
        return Range(mk2::iterator::advance(mk2::iterator::begin(r), range.first_),
                     mk2::iterator::advance(mk2::iterator::begin(r), range.end_));
    }
    
    inline constexpr ranged_tag ranged(size_t first, size_t end)
    {
        return ranged_tag(first, end);
    }
}
}
}
