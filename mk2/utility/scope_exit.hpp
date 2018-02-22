//
// Created by Himatya on 2018/02/22.
//

#ifndef LIBMK2_UTILITY_SCOPE_EXIT_HPP
#define LIBMK2_UTILITY_SCOPE_EXIT_HPP

#include <mk2/utility/apply.hpp>

namespace mk2 {
namespace utility {
    template<class Function, class... Args>
    class scope_exit
    {
        Function f_;
        std::tuple<Args...> args_;

    public:
        constexpr scope_exit(Function&& f, Args&&... args)
            : f_(std::forward<Function>(f)), args_(std::forward<Args>(args)...)
        {}

        ~scope_exit()
        {
            mk2::utility::apply(std::move(f_), std::move(args_));
        }
    };

    template<class Function, class... Args>
    constexpr decltype(auto) make_scope_exit(Function&& f, Args&&... args)
    {
        return scope_exit<Function, Args...>(std::forward<Function>(f), std::forward<Args>(args)...);
    }
}
}

#endif //LIBMK2_UTILITY_SCOPE_EXIT_HPP