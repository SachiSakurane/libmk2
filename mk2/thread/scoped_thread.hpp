//
// Created by Himatya on 2018/01/12.
//

#ifndef LIBMK2_THREAD_SCOPED_THREAD_HPP
#define LIBMK2_THREAD_SCOPED_THREAD_HPP

#include <thread>
#include <tuple>
#include <utility>

#include <mk2/utility/noncopyable.hpp>

namespace mk2 {
namespace thread{
    template<class Thread>
    class basic_scoped_thread : mk2::utility::noncopyable<basic_scoped_thread<Thread>>
    {
    public:
        basic_scoped_thread() = default;

        template<class F, class... Args>
        explicit basic_scoped_thread(F&& f, Args&&... args) : thread_(std::forward<F>(f), std::forward<Args>(args)...)
        {}

        basic_scoped_thread(basic_scoped_thread&& obj) noexcept
            : thread_{ std::move(obj.thread_) }
        {}

        basic_scoped_thread& operator=(basic_scoped_thread&& rhv) noexcept
        {
            if (thread_.joinable())
                thread_.join();
            this->thread_ = std::move(rhv.thread_);
            return *this;
        }
        
        ~basic_scoped_thread()
        {
            join();
        }
        
        void join()
        {
            if (thread_.joinable())
                thread_.join();
        }
        
        void detach()
        {
            if (thread_.joinable())
                thread_.detach();
        }

        Thread& get_thread() { return thread_; }

    private:
        Thread thread_;
    };

    using scoped_thread = mk2::thread::basic_scoped_thread<std::thread>;
}
}

#endif