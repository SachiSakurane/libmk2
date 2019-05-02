//
// Created by Himatya on 2018/04/26.
//

#ifndef LIBMK2_ITERATOR_SELECT_ITERATOR_HPP
#define LIBMK2_ITERATOR_SELECT_ITERATOR_HPP

#include <utility>
#include <iterator>
#include <tuple>

namespace mk2{
namespace iterator{
    
    template<class Iterator, class UnaryFunction>
    class select_iterator
    {
        Iterator i_;
        UnaryFunction f_;

    public:
        using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
        using value_type        = typename std::result_of<UnaryFunction&(typename std::iterator_traits<Iterator>::value_type)>::type;
        using difference_type   = typename std::iterator_traits<Iterator>::difference_type;
        using pointer           = typename std::iterator_traits<Iterator>::pointer;
        using reference         = select_iterator::value_type&;

        constexpr select_iterator(Iterator&& i, UnaryFunction&& f) noexcept :
                i_(std::forward<Iterator>(i)), f_(std::forward<UnaryFunction>(f)){};

        constexpr auto clone(Iterator&& i) -> decltype(auto)
        {
            select_iterator it = *this;
            it.i_ = std::forward<Iterator>(i);
            return it;
        }

        constexpr auto get() -> decltype(auto)
        {
            return i_;
        }

        constexpr auto get() const -> decltype(auto)
        {
            return i_;
        }

        constexpr auto operator *() -> decltype(auto)
        {
            return f_(i_.operator*());
        }

        constexpr auto operator *() const -> decltype(auto)
        {
            return f_(i_.operator*());
        }

        constexpr auto operator ->() -> decltype(auto)
        {
            return f_(i_.operator->());
        }

        constexpr auto operator ->() const -> decltype(auto)
        {
            return f_(i_.operator->());
        }

        constexpr auto operator[](difference_type rhv) -> decltype(auto)
        {
            return f_(i_.operator[](rhv));
        }

        constexpr auto operator[](difference_type rhv) const -> decltype(auto)
        {
            return f_(i_.operator[](rhv));
        }

        constexpr select_iterator& operator ++()
        {
            ++i_;
            return *this;
        }

        constexpr select_iterator& operator --()
        {
            --i_;
            return *this;
        }

        constexpr const select_iterator operator ++(int)
        {
            select_iterator t = *this;
            ++t.i_;
            return t;
        }

        constexpr const select_iterator operator --(int)
        {
            select_iterator t = *this;
            --t.i_;
            return t;
        }

        constexpr select_iterator& operator +=(difference_type rhv)
        {
            i_ += rhv;
            return *this;
        }

        constexpr select_iterator& operator -=(difference_type rhv)
        {
            i_ -= rhv;
            return *this;
        }

        template<class Iterator_, class UnaryFunction_>
        friend constexpr void swap(select_iterator<Iterator_, UnaryFunction_>&, select_iterator<Iterator_, UnaryFunction_>&);
    };

    template<class Iterator, class UnaryFunction>
    constexpr void swap(select_iterator<Iterator, UnaryFunction> &lhv, select_iterator<Iterator, UnaryFunction> &rhv)
    {
        select_iterator<Iterator, UnaryFunction> tmp(std::move(lhv));
        lhv = std::move(rhv);
        rhv = std::move(tmp);
    }

    template<
        class Iterator1, class UnaryFunction1, class Iterator2, class UnaryFunction2,
        typename = typename std::enable_if_t<
            std::is_base_of<std::input_iterator_tag,
                            typename std::iterator_traits<Iterator1>::iterator_category>::value &&
            std::is_base_of<std::input_iterator_tag,
                            typename std::iterator_traits<Iterator2>::iterator_category>::value
        >
    >
    constexpr bool operator==(const mk2::iterator::select_iterator<Iterator1, UnaryFunction1> &lhv,
                              const mk2::iterator::select_iterator<Iterator2, UnaryFunction2> &rhv)
    {
        return lhv.get() == rhv.get();
    }

    template<
        class Iterator1, class UnaryFunction1, class Iterator2, class UnaryFunction2,
        typename = typename std::enable_if_t<
            std::is_base_of<std::input_iterator_tag,
                            typename std::iterator_traits<Iterator1>::iterator_category>::value &&
            std::is_base_of<std::input_iterator_tag,
                            typename std::iterator_traits<Iterator2>::iterator_category>::value
        >
    >
    constexpr bool operator!=(const mk2::iterator::select_iterator<Iterator1, UnaryFunction1> &lhv,
                              const mk2::iterator::select_iterator<Iterator2, UnaryFunction2> &rhv)
    {
        return !(lhv == rhv);
    }

    template<
        class Iterator1, class UnaryFunction1, class Iterator2, class UnaryFunction2,
        typename = typename std::enable_if_t<
            std::is_base_of<std::random_access_iterator_tag,
                            typename std::iterator_traits<Iterator1>::iterator_category>::value &&
            std::is_base_of<std::random_access_iterator_tag,
                            typename std::iterator_traits<Iterator2>::iterator_category>::value
        >
    >
    constexpr bool operator<(const mk2::iterator::select_iterator<Iterator1, UnaryFunction1> &lhv,
                             const mk2::iterator::select_iterator<Iterator2, UnaryFunction2> &rhv)
    {
        return lhv.get() < rhv.get();
    }

    template<
        class Iterator1, class UnaryFunction1, class Iterator2, class UnaryFunction2,
        typename = typename std::enable_if_t<
            std::is_base_of<std::random_access_iterator_tag,
                            typename std::iterator_traits<Iterator1>::iterator_category>::value &&
            std::is_base_of<std::random_access_iterator_tag,
                            typename std::iterator_traits<Iterator2>::iterator_category>::value
        >
    >
    constexpr bool operator>(const mk2::iterator::select_iterator<Iterator1, UnaryFunction1> &lhv,
                             const mk2::iterator::select_iterator<Iterator2, UnaryFunction2> &rhv)
    {
        return lhv.get() > rhv.get();
    }

    template<
        class Iterator1, class UnaryFunction1, class Iterator2, class UnaryFunction2,
        typename = typename std::enable_if_t<
            std::is_base_of<std::random_access_iterator_tag,
                            typename std::iterator_traits<Iterator1>::iterator_category>::value &&
            std::is_base_of<std::random_access_iterator_tag,
                            typename std::iterator_traits<Iterator2>::iterator_category>::value
        >
    >
    constexpr bool operator<=(const mk2::iterator::select_iterator<Iterator1, UnaryFunction1> &lhv,
                              const mk2::iterator::select_iterator<Iterator2, UnaryFunction2> &rhv)
    {
        return lhv.get() <= rhv.get();
    }

    template<
        class Iterator1, class UnaryFunction1, class Iterator2, class UnaryFunction2,
        typename = typename std::enable_if_t<
            std::is_base_of<std::random_access_iterator_tag,
                            typename std::iterator_traits<Iterator1>::iterator_category>::value &&
            std::is_base_of<std::random_access_iterator_tag,
                            typename std::iterator_traits<Iterator2>::iterator_category>::value
        >
    >
    constexpr bool operator>=(const mk2::iterator::select_iterator<Iterator1, UnaryFunction1> &lhv,
                              const mk2::iterator::select_iterator<Iterator2, UnaryFunction2> &rhv)
    {
        return lhv.get() >= rhv.get();
    }

    template<
        class Iterator, class UnaryFunction,
        typename = typename std::enable_if_t<
            std::is_base_of<
                std::random_access_iterator_tag,
                typename std::iterator_traits<Iterator>::iterator_category>::value
        >
    >
    constexpr select_iterator<Iterator, UnaryFunction> operator+(
            const select_iterator<Iterator, UnaryFunction> &iter,
            typename std::iterator_traits<select_iterator<Iterator, UnaryFunction>>::difference_type d)
    {
        return iter.get() + d;
    }

    template<
        class Iterator, class UnaryFunction,
        typename = typename std::enable_if_t<
            std::is_base_of<
                std::random_access_iterator_tag,
                typename std::iterator_traits<Iterator>::iterator_category>::value
        >
    >
    constexpr select_iterator<Iterator, UnaryFunction> operator+(
            typename std::iterator_traits<select_iterator<Iterator, UnaryFunction>>::difference_type d,
            const select_iterator<Iterator, UnaryFunction> &iter)
    {
        return d + iter.get();
    }

    template<
        class Iterator, class UnaryFunction,
        typename = typename std::enable_if_t<
            std::is_base_of<
                std::random_access_iterator_tag,
                typename std::iterator_traits<Iterator>::iterator_category>::value
        >
    >
    constexpr select_iterator<Iterator, UnaryFunction> operator-(
            const select_iterator<Iterator, UnaryFunction> &iter,
            typename std::iterator_traits<select_iterator<Iterator, UnaryFunction>>::difference_type d)
    {
        return iter.get() - d;
    }

    template<
        class Iterator, class UnaryFunction,
        typename = typename std::enable_if_t<
            std::is_base_of<
                std::random_access_iterator_tag,
                typename std::iterator_traits<Iterator>::iterator_category>::value
        >
    >
    constexpr typename std::iterator_traits<select_iterator<Iterator, UnaryFunction>>::difference_type operator-(
            const select_iterator<Iterator, UnaryFunction> &lhv,
            const select_iterator<Iterator, UnaryFunction> &rhv)
    {
        return lhv.get() - rhv.get();
    }



    template<class InputIterator, class UnaryFunction>
    constexpr auto make_select_iterator(InputIterator &&i, UnaryFunction &&f)
    {
        return mk2::iterator::select_iterator<InputIterator, UnaryFunction>(
                std::forward<InputIterator>(i), std::forward<UnaryFunction>(f));
    }
}
}

#endif //LIBMK2_ITERATOR_SELECT_ITERATOR_HPP
