//
// Created by Himatya on 2018/01/12.
//

#ifndef LIBMK2_UTILITY_APPLY_HPP
#define LIBMK2_UTILITY_APPLY_HPP

#include <tuple>
#include <utility>

namespace mk2 {
namespace utility {

    namespace detail
    {
        template<class F, class Tuple, size_t... Indices>
        auto apply_impl(F&& f, const Tuple& args, std::index_sequence<Indices...>)
        {
            return std::forward<F>(f)(std::get<Indices>(args)...);
        }

        template<class F, class Tuple, size_t... Indices>
        auto apply_impl(F&& f, Tuple&& args, std::index_sequence<Indices...>)
        {
            return std::forward<F>(f)(std::get<Indices>(std::forward<Tuple>(args))...);
        }
    }

    template<class F, class Tuple>
    auto apply(F&& f, const Tuple& args)
    {
        return mk2::utility::detail::apply_impl(std::forward<F>(f), args,
                                                std::make_index_sequence<std::tuple_size<Tuple>::value>());
    }

    template<class F, class Tuple>
    auto apply(F&& f, Tuple&& args)
    {
        return mk2::utility::detail::apply_impl(std::forward<F>(f), std::forward<Tuple>(args),
                                                std::make_index_sequence<std::tuple_size<Tuple>::value>());
    }

    template<class F>
    class apply_functor
    {
    public:
        explicit apply_functor(F&& f) : f_(std::forward<F>(f)){}

        template<class Tuple>
        auto operator ()(Tuple&& t)
        {
            return mk2::utility::apply(f_, std::forward<Tuple>(t));
        }

        template<class Tuple>
        auto operator ()(const Tuple& t)
        {
            return mk2::utility::apply(f_, t);
        }

    private:
        F f_;
    };

    template<class F, class Tuple>
    auto make_apply(F&& f)
    {
        return mk2::utility::apply_functor<F>(std::forward<F>(f));
    }
}
}

#endif //LIBMK2_UTILITY_APPLY_HPP
