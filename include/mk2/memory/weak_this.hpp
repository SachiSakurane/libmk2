//
// Created by Himatya on 2019/11/30.
//

#pragma once

#include <memory>
#include <type_traits>

namespace mk2 {
namespace memory {

    template <class Type, typename = typename std::enable_if<std::is_base_of_v<std::enable_shared_from_this<Type>, Type>>::type>
    class weak_this_helper : public std::weak_ptr<Type>
    {
    public:
        weak_this_helper() = default;

        explicit weak_this_helper(Type& _this) : std::weak_ptr<Type>(_this.weak_from_this()) {}
    };

    template <class Type, typename = typename std::enable_if<std::is_base_of_v<std::enable_shared_from_this<Type>, Type>>::type>
    weak_this_helper<Type> weak_this(Type& _this)
    {
        return weak_this_helper<Type>(_this);
    }

    template <class Type, typename = typename std::enable_if<std::is_base_of_v<std::enable_shared_from_this<Type>, Type>>::type>
    weak_this_helper<Type> weak_this(Type* _this)
    {
        if (!_this) {
            return weak_this_helper<Type>();
        }
        return weak_this_helper<Type>(*_this);
    }

}
}
