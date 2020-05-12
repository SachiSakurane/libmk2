//
// Created by Himatya on 2020/05/13.
//

#pragma once

#include <mk2/utility/noncopyable.hpp>

namespace mk2 {
namespace rx {
    template <class Type>
    class has_dispose_bag : private mk2::utility::noncopyable<Type>{
    protected:
        mk2::rx::dispose_bag bag;
    };
}
}
