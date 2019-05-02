//
//  containerizer.hpp
//
//
//  Created by Himatya on 2017/01/29.
//  Copyright © 2017年 Himatya. All rights reserved.
//

#pragma once

#include <mk2/iterator/begin.hpp>
#include <mk2/iterator/end.hpp>

namespace mk2{
namespace range{
    namespace adaptors{
        
        template<class Range>
        class containerizer
        {
        public:
            constexpr containerizer(const Range& r) noexcept : range_(r){}
            
            template<class To>
            constexpr operator To() const
            {
                return To(mk2::iterator::cbegin(range_), mk2::iterator::cend(range_));
            }
            
            template<class To>
            constexpr operator To()
            {
                return To(mk2::iterator::begin(range_), mk2::iterator::end(range_));
            }
            
        private:
            const Range& range_;
        };
        
        template<class Range>
        constexpr inline containerizer<Range> containerize(Range&& range)
        {
            return containerizer<Range>(std::forward<Range>(range));
        }
        
        struct containerized_tag{};
        constexpr containerized_tag containerized{};
        
        template<class Range>
        constexpr inline containerizer<Range> operator|(Range&& range, containerized_tag)
        {
            return containerize(std::forward<Range>(range));
        }
    }
}
}

