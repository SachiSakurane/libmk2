//
// Created by Himatya on 2018/06/13.
//

#pragma once

#include <tuple>

namespace mk2 {
namespace tuple {
    
    namespace detail
    {
        template<size_t Begin, size_t End, bool IsEnd = Begin + 1 == End>
        struct execute_impl;
    
        template<size_t Begin, size_t End>
        struct execute_impl<Begin, End, true>
        {
            template<typename Tuple, typename F, typename... Args>
            static void execute(Tuple&& tuple, F&& f, Args&&... args)
            {
                f(std::get<Begin>(tuple), std::forward<Args>(args)...);
            }
        };
    
        template<size_t Begin, size_t End>
        struct execute_impl<Begin, End, false>
        {
            template<typename Tuple, typename F, typename... Args>
            static void execute(Tuple&& tuple, F&& f, Args&&... args)
            {
                execute_impl<Begin, (Begin + End) / 2>::execute
                    (std::forward<Tuple>(tuple), std::forward<F>(f), std::forward<Args>(args)...);
            
                execute_impl<(Begin + End) / 2, End>::execute
                    (std::forward<Tuple>(tuple), std::forward<F>(f), std::forward<Args>(args)...);
            }
        };
    }
    
    template<typename Tuple, typename F, typename... Args>
    void execute(Tuple&& tuple, F&& f, Args&&... args)
    {
        mk2::tuple::detail::execute_impl<0, std::tuple_size<std::remove_reference_t<Tuple>>::value>::execute(
            std::forward<Tuple>(tuple),
            std::forward<F>(f),
            std::forward<Args>(args)...
        );
    }
    
    template<std::size_t Begin, std::size_t End, typename Tuple, typename F, typename... Args>
    void execute(Tuple&& tuple, F&& f, Args&&... args)
    {
        mk2::tuple::detail::execute_impl<Begin, End>::execute(
            std::forward<Tuple>(tuple),
            std::forward<F>(f),
            std::forward<Args>(args)...
        );
    }
}
}