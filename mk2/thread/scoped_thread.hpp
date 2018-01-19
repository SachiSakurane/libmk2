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
    template<class Thread = std::thread>
    class scoped_thread : mk2::utility::noncopyable<scoped_thread>
    {
    public:
        scoped_thread()
        {}
        
        template<class F, class... Args>
        scoped_thread(F&& f, Args&&... args) : thread_(std::forward<F>(f), std::forward<Args>(args)...)
        {}

        scoped_thread(scoped_thread&& obj) noexcept 
            : thread_{ std::move(obj.thread_) }
        {}

        scoped_thread& operator=(scoped_thread&& rhv) noexcept
        {
            if (thread_.joinable())
                thread_.join();
            this->thread_ = std::move(rhv.thread_);
            return *this;
        }
        
        ~scoped_thread()
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
}
}

#endif