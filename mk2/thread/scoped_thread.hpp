//
// Created by Himatya on 2018/01/12.
//

#ifndef LIBMK2_THREAD_SCOPED_THREAD_HPP
#define LIBMK2_THREAD_SCOPED_THREAD_HPP

#include <functional>
#include <thread>
#include <tuple>
#include <utility>

#include <mk2/utility/noncopyable.hpp>

namespace mk2 {
namespace thread{
    namespace detail
    {
        template<class F>
        void no_return(F&& f)
        {
            std::forward<F>(f)();
        }
    
        template<class F, class Tuple, size_t... Indices>
        auto bind_func_impl(F&& f, Tuple&& args, std::index_sequence<Indices...>)
        {
            return std::bind(no_return, 
                             std::bind(std::forward<F>(f), std::get<Indices>(std::forward<Tuple>(args))...));
        }
    
        template<class F, class Tuple>
        auto bind_func(F&& f, Tuple&& tuple)
        {
            return bind_func_impl(std::forward<F>(f), std::forward<Tuple>(args),
                                  std::make_index_sequence<std::tuple_size<Tuple>::value>());
        }
    }

    class scoped_thread : mk2::utility::noncopyable<scoped_thread>
    {
    public:
        scoped_thread()
        {}
        
        template<class F, class... Args>
        scoped_thread(F&& f, Args&&... args) : thread_(std::forward<F>(f), std::forward<Args>(args)...)
        {}
        
        template<
                class ThreadFunc, class ThreadTupleArgs,
                class FinalizeFunc, class FinalizeTupleArgs
        >
        scoped_thread(ThreadFunc&& thread_func, ThreadTupleArgs&& thread_tuple,
                    FinalizeFunc&& finalize_func, FinalizeTupleArgs&& finalize_tuple)
            : thread_(mk2::thread::detail::bind_func(thread_func, thread_tuple)),
              finalizer_(mk2::thread::detail::bind_func(finalize_func, finalize_tuple))
        {}

        scoped_thread(scoped_thread&& obj) noexcept 
            : thread_{ std::move(obj.thread_) },
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

        std::thread& get_thread() { return thread_; }
        
        template<class F, class ...Args>
        void set_finalizer(F&& f, Args&&... args)
        {
            finalizer_ = std::bind(mk2::thread::detail::no_return,
                                   std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        }

    private:
        std::thread thread_;
        std::function<void()> finalizer_;
    };
}
}

#endif