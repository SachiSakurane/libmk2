 //
// Created by Himatya on 2018/05/22.
//

#pragma once

#include <chrono>
#include <vector>
#include <iterator>

#include <boost/optional.hpp>

namespace mk2 {
namespace chrono {

    namespace detail
    {
        class frame_counter_container
        {
        public:
            frame_counter_container(std::chrono::nanoseconds range) : range_(range) {}

            void push(std::chrono::nanoseconds ns)
            {
                while (time_ + (ns - time_split_.front()) > range_)
                {
                    time_ -= time_split_.front();
                    time_split_.erase(std::begin(time_split_));
                }
                time_ += ns;
                time_split_.emplace_back(ns);
            }

            bool is_valid() const
            { return range_ <= time_; }

            auto get_time() const
            { return time_; }

            auto get_range() const
            { return range_; }

            auto get_frame() const
            { return time_split_.size(); }

        private:
            std::vector<std::chrono::nanoseconds> time_split_;
            std::chrono::nanoseconds range_;
            std::chrono::nanoseconds time_;
        };
    }

    class frame_counter
    {
    public:
        frame_counter(std::chrono::nanoseconds range) : container_(range) {}

        ~frame_counter() = default;

        void tick()
        {
            auto point = std::chrono::steady_clock::now();
            auto dlt = point - time_point_;
            container_.push(std::chrono::duration_cast<std::chrono::milliseconds>(dlt));
            time_point_ = point;
        }

        boost::optional<double> get_fps()
        {
            if(!container_.is_valid())
                return boost::none;

            return (double)container_.get_frame().count() * container_.get_time().count() / container_.get_range().count();
        }

    private:
        std::chrono::time_point time_point_;
        mk2::chrono::detail::frame_counter_container container_;
    };

}
}