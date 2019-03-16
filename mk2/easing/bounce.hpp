//
//  bounce.hpp
//
//
//  Created by Himatya on 2017/05/26.
//  Copyright (c) 2017 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

namespace mk2{
namespace easing{
    template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline constexpr T bounce(T normalized_time) {
	    T rvs_time = 1.0 - normalized_time;
	    if (rvs_time < (1.0 / 2.75)) {
	    	return 1.0 - 7.5625 * rvs_time * rvs_time;
	    }
	    else if (rvs_time < (2.0 / 2.75)) {
		    T post_fix = rvs_time - (1.5f / 2.75f);
		    return - 7.5625 * rvs_time * post_fix + 0.25;
	    }
	    else if (rvs_time < (2.5 / 2.75)) {
	    	T post_fix = rvs_time - (2.25f / 2.75f);
	    	return -7.5625 * rvs_time * post_fix + 0.0625;
	    }
	    else {
	    	T post_fix = rvs_time - (2.625f / 2.75f);
	    	return -7.5625 * rvs_time * post_fix + 0.015625;
	    }
    }
}
}
