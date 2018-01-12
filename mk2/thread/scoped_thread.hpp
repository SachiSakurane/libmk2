//
// Created by Himatya on 2018/01/12.
//

#ifndef LIBMK2_THREAD_SCOPED_THREAD_HPP
#define LIBMK2_THREAD_SCOPED_THREAD_HPP

#include <thread>
#include <functional>

#include <mk2/utility/noncopyable.hpp>

//safe_threadの方がいいかも
namespace mk2 {
namespace thread{
    class scoped_thread : mk2::utility::noncopyable<scoped_thread>
    {
    public:
        scoped_thread()
        {}
        
        template<class F, class ...Args>
        scoped_thread(F&& f, Args&&... args) : thread_{ std::forward<F>(f), std::forward<Args>(args)... }
        {}
        
        //finalizer込みのコンストラクタ
        
        scoped_thread(scoped_thread&& obj) noexcept :
            thread_{ std::move(obj.thread_) },
            finalizer_{ std::move(obj.finalizer_) }
        {}

        scoped_thread& operator=(scoped_thread&& rhv) noexcept
        {
            if (finalizer_)
                finalizer_();
            if (thread_.joinable())
                thread_.join();
            this->thread_ = std::move(rhv.thread_);
            this->finalizer_ = std::move(rhv.finalizer_);
            return *this;
        }
        
        ~scoped_thread()
        {
            if (finalizer_) 
                finalizer_();
            if (thread_.joinable())
                thread_.join();
        }
        
        decltype(thread_)& get_thread() { return thread_; }
        decltype(finalizer_)& get_finalizer() { return finalizer_; }

    private:
        std::thread thread_;
        std::function<void()> finalizer_;
    };
}
}

#endif