 //
// Created by Himatya on 2018/05/22.
//

#pragma once

#include <chrono>

namespace mk2 {
namespace chrono {

    namespace detail
    {
        class fps_counter_container
        {

        };
    }

    class fps_counter
    {
    public:
        fps_counter();
        ~fps_counter() = default;

        void tick();

        double get_fps();

    private:
    };

}
}