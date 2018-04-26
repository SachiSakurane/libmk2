//
// Created by Himatya on 2018/04/26.
//

#ifndef LIBMK2_ITERATOR_SELECT_ITERATOR_HPP
#define LIBMK2_ITERATOR_SELECT_ITERATOR_HPP

#include <utility>

namespace mk2{
namespace iterator{
    template<class InputIterator, class UnaryFunction>
    class select_iterator : public InputIterator
    {
        using base = InputIterator;
        UnaryFunction f;

    public:
        using iterator_category = typename base::iterator_category;
        using value_type        = typename base::value_type;
        using difference_type   = typename base::difference_type;
        using pointer           = typename base::pointer;
        using reference         = typename base::reference;

        constexpr select_iterator(InputIterator&& i, UnaryFunction&& f) noexcept :
                base(std::forward(i)), f(std::forward(f)){}

        constexpr auto operator *()
        {
            return f(base::operator*());
        }

        constexpr auto operator *() const
        {
            return f(base::operator*());
        }

        constexpr auto operator ->()
        {
            return f(base::operator->());
        }

        constexpr auto operator ->() const
        {
            return f(base::operator->());
        }

        constexpr auto operator[](typename base::difference_type rhv)
        {
            return f(base::operator[](rhv));
        }

        constexpr auto operator[](typename base::difference_type rhv) const
        {
            return f(base::operator[](rhv));
        }
    };

    template<class InputIterator, class UnaryFunction>
    auto make_select_iterator(InputIterator&& i, UnaryFunction&& f)
    {
        return mk2::iterator::select_iterator<InputIterator, UnaryFunction>(std::forward(i), std::forward(f));
    }
}
}

#endif //LIBMK2_ITERATOR_SELECT_ITERATOR_HPP
