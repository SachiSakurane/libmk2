//
// Created by Himatya on 2019/12/01.
//

#pragma once

#include <rxcpp/rx.hpp>
#include <mk2/rx/dispose_bag.hpp>

namespace mk2 {
namespace rx {
    class disposed_tag {
    public:
        explicit disposed_tag(mk2::rx::dispose_bag& bag) : bag_{bag} {}

        void push(rxcpp::composite_subscription&& subscription) {
            bag_.push(std::move(subscription));
        }

    private:
        mk2::rx::dispose_bag& bag_;
    };

    inline void operator | (rxcpp::composite_subscription&& subscription, mk2::rx::disposed_tag bag) {
        bag.push(std::move(subscription));
    }

    inline disposed_tag disposed(mk2::rx::dispose_bag& by) {
        return disposed_tag{by};
    }
}
}