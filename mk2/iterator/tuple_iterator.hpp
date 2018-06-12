//
// Created by Himatya on 2018/06/13.
//

#pragma once

#include <cstddef>
#include <iterator>
#include <tuple>

#include <mk2/container/container_traits.hpp>
#include <mk2/tuple/execute.hpp>

namespace mk2{
namespace iterator{
    
    namespace detail
    {
        template<class Iter, class Top, class... Iterator>
        struct tuple_iterator_category_impl0
        {
            typedef typename tuple_iterator_category_impl0<
                std::conditional_t<
                    std::is_base_of<Iter, typename std::iterator_traits<Top>::iterator_category>::value,
                    Iter,
                    typename std::iterator_traits<Top>::iterator_category
                >, Iterator...>::type type;
        };
    
        template<class Iter, class Top>
        struct tuple_iterator_category_impl0<Iter, Top>
        {
            typedef std::conditional_t<
                std::is_base_of<Iter, typename std::iterator_traits<Top>::iterator_category>::value,
                Iter,
                typename std::iterator_traits<Top>::iterator_category
            > type;
        };
        
        template<class Top, class... Iterator>
        struct tuple_iterator_category
        {
            typedef typename tuple_iterator_category_impl0<typename std::iterator_traits<Top>::iterator_category, Iterator...>::type type;
        };
        
        template<class Top>
        struct tuple_iterator_category<Top>
        {
            typedef typename std::iterator_traits<Top>::iterator_category type;
        };
        
        struct add_pointer
        {
            template<class Type>
            auto constexpr operator()(Type&& t){
                return t.operator*();
            }
        };
    
        struct add_arrow
        {
            template<class Type>
            auto constexpr operator()(Type&& t){
                return t.operator->();
            }
        };
    
        struct add_nest
        {
            template<class Type, class D>
            auto constexpr operator()(Type&& t, D n){
                return t.operator[](n);
            }
        };
    
        struct pre_increment
        {
            template<class Type>
            void constexpr operator()(Type&& t){
                ++t;
            }
        };
    
        struct post_increment
        {
            template<class Type>
            void constexpr operator()(Type&& t){
                t++;
            }
        };
    
        struct pre_decrement
        {
            template<class Type>
            void constexpr operator()(Type&& t){
                --t;
            }
        };
    
        struct post_decrement
        {
            template<class Type>
            void constexpr operator()(Type&& t){
                t--;
            }
        };
    
        struct plus_assignment
        {
            template<class Type, class D>
            void constexpr operator()(Type&& t, D n){
                t += n;
            }
        };
    
        struct minus_assignment
        {
            template<class Type, class D>
            void constexpr operator()(Type&& t, D n){
                t -= n;
            }
        };
    
        struct operator_plus
        {
            operator_plus(size_t n) : n_(n) {}
        
            template<class Type>
            auto constexpr operator()(Type&& t){
                return t + n_;
            }
    
        private:
            size_t n_;
        };
    
        struct operator_plus_swp
        {
            operator_plus_swp(size_t n) : n_(n) {}
        
            template<class Type>
            auto constexpr operator()(Type&& t){
                return n_ + t;
            }
    
        private:
            size_t n_;
        };
    
        struct operator_minus
        {
            operator_minus(size_t n) : n_(n) {}
        
            template<class Type>
            auto constexpr operator()(Type&& t){
                return t - n_;
            }
    
        private:
            size_t n_;
        };
    
        template<class F, class Tuple, size_t... Indices>
        constexpr auto make_original_tuple_impl(F&& f, Tuple&& tuple, std::index_sequence<Indices...>)
        {
            return std::make_tuple(std::forward<F>(f)(std::get<Indices>(std::forward<Tuple>(tuple)))...);
        }
    
        template<class F, class Tuple>
        constexpr auto make_original_tuple(F&& f, Tuple&& tuple)
        {
            return make_original_tuple_impl(std::forward<F>(f), std::forward<Tuple>(tuple), std::make_index_sequence<std::tuple_size<std::remove_reference_t<Tuple>>::value>());
        }
    
        template<class Tuple, size_t... Indices>
        constexpr auto make_original_tuple_minus_impl(Tuple&& lhv, Tuple&& rhv, std::index_sequence<Indices...>)
        {
            return std::make_tuple((std::get<Indices>(std::forward<Tuple>(lhv)) - std::get<Indices>(std::forward<Tuple>(rhv)))...);
        }
    
        template<class Tuple>
        constexpr auto make_original_tuple_minus(Tuple&& lhv, Tuple&& rhv)
        {
            return make_original_tuple_minus_impl(
                std::forward<Tuple>(lhv), std::forward<Tuple>(rhv),
                std::make_index_sequence<std::tuple_size<std::remove_reference_t<Tuple>>::value>());
        }
    }
    
    template<class... Iterator>
    class tuple_iterator
    {
    public:
        using iterator_category = typename mk2::iterator::detail::tuple_iterator_category<Iterator...>::type ;
        using value_type        = std::tuple<typename std::iterator_traits<Iterator>::value_type...>;
        using difference_type   = size_t;
        using pointer           = std::tuple<typename std::iterator_traits<Iterator>::pointer...>;
        using reference         = std::tuple<typename std::iterator_traits<Iterator>::reference...>;
        
        constexpr tuple_iterator(Iterator&&... args) : iters_{std::forward<Iterator>(args)...} {}
    
        constexpr auto get() -> decltype(auto)
        {
            return iters_;
        }
    
        constexpr auto get() const -> decltype(auto)
        {
            return iters_;
        }
    
        constexpr auto operator *() -> decltype(auto)
        {
            return mk2::iterator::detail::make_original_tuple(mk2::iterator::detail::add_pointer(), iters_);
        }
    
        constexpr auto operator *() const -> decltype(auto)
        {
            return mk2::iterator::detail::make_original_tuple(mk2::iterator::detail::add_pointer(), iters_);
        }
    
        constexpr auto operator ->() -> decltype(auto)
        {
            return mk2::iterator::detail::make_original_tuple(mk2::iterator::detail::add_arrow(), iters_);
        }
    
        constexpr auto operator ->() const -> decltype(auto)
        {
            return mk2::iterator::detail::make_original_tuple(mk2::iterator::detail::add_arrow(), iters_);
        }
    
        constexpr auto operator[](difference_type n) -> decltype(auto)
        {
            return mk2::iterator::detail::make_original_tuple(
                std::bind(mk2::iterator::detail::add_nest(), std::placeholders::_1, n), iters_);
        }
    
        constexpr auto operator[](difference_type n) const -> decltype(auto)
        {
            return mk2::iterator::detail::make_original_tuple(
                std::bind(mk2::iterator::detail::add_nest(), std::placeholders::_1, n), iters_);
        }
    
        constexpr tuple_iterator& operator ++()
        {
            mk2::tuple::execute(iters_, mk2::iterator::detail::pre_increment());
            return *this;
        }
    
        constexpr tuple_iterator& operator --()
        {
            mk2::tuple::execute(iters_, mk2::iterator::detail::pre_decrement());
            return *this;
        }
    
        constexpr const tuple_iterator operator ++(int)
        {
            tuple_iterator t = *this;
            mk2::tuple::execute(t.iters_, mk2::iterator::detail::post_increment());
            return t;
        }
    
        constexpr const tuple_iterator operator --(int)
        {
            tuple_iterator t = *this;
            mk2::tuple::execute(t.iters_, mk2::iterator::detail::post_decrement());
            return t;
        }
    
        constexpr tuple_iterator& operator +=(difference_type n)
        {
            mk2::tuple::execute(iters_, mk2::iterator::detail::plus_assignment(), n);
            return *this;
        }
    
        constexpr tuple_iterator& operator -=(difference_type n)
        {
            mk2::tuple::execute(iters_, mk2::iterator::detail::minus_assignment(), n);
            return *this;
        }
        
        constexpr void swap(tuple_iterator& lhv, tuple_iterator& rhv)
        {
            tuple_iterator tmp{std::move(lhv)};
            lhv = std::move(rhv);
            rhv = std::move(tmp);
        }

    private:
        std::tuple<Iterator...> iters_;
        
    };
    
    template<class... Iterator>
    constexpr bool operator==(const mk2::iterator::tuple_iterator<Iterator...> &lhv,
                              const mk2::iterator::tuple_iterator<Iterator...> &rhv)
    {
        return lhv.get() == rhv.get();
    }
    
    template<class... Iterator>
    constexpr bool operator!=(const mk2::iterator::tuple_iterator<Iterator...> &lhv,
                              const mk2::iterator::tuple_iterator<Iterator...> &rhv)
    {
        return !(lhv == rhv);
    }
    
    template<class... Iterator>
    constexpr bool operator< (const mk2::iterator::tuple_iterator<Iterator...> &lhv,
                              const mk2::iterator::tuple_iterator<Iterator...> &rhv)
    {
        return lhv.get() < rhv.get();
    }
    
    template<class... Iterator>
    constexpr bool operator> (const mk2::iterator::tuple_iterator<Iterator...> &lhv,
                              const mk2::iterator::tuple_iterator<Iterator...> &rhv)
    {
        return lhv.get() > rhv.get();
    }
    
    template<class... Iterator>
    constexpr bool operator<=(const mk2::iterator::tuple_iterator<Iterator...> &lhv,
                              const mk2::iterator::tuple_iterator<Iterator...> &rhv)
    {
        return lhv.get() <= rhv.get();
    }
    
    template<class... Iterator>
    constexpr bool operator>=(const mk2::iterator::tuple_iterator<Iterator...> &lhv,
                              const mk2::iterator::tuple_iterator<Iterator...> &rhv)
    {
        return lhv.get() >= rhv.get();
    }
    
    template<class... Iterator>
    constexpr mk2::iterator::tuple_iterator<Iterator...> operator+(
        const mk2::iterator::tuple_iterator<Iterator...> &iter,
        typename std::iterator_traits<mk2::iterator::tuple_iterator<Iterator...>>::difference_type d)
    {
        return mk2::iterator::detail::make_original_tuple(mk2::iterator::detail::operator_plus(d), iter.get());
    }
    
    template<class... Iterator>
    constexpr mk2::iterator::tuple_iterator<Iterator...> operator+(
        typename std::iterator_traits<mk2::iterator::tuple_iterator<Iterator...>>::difference_type d,
        const mk2::iterator::tuple_iterator<Iterator...> &iter)
    {
        return mk2::iterator::detail::make_original_tuple(mk2::iterator::detail::operator_plus_swp(d), iter.get());
    }
    
    template<class... Iterator>
    constexpr mk2::iterator::tuple_iterator<Iterator...> operator-(
        const mk2::iterator::tuple_iterator<Iterator...> &iter,
        typename std::iterator_traits<mk2::iterator::tuple_iterator<Iterator...>>::difference_type d)
    {
        return mk2::iterator::detail::make_original_tuple(mk2::iterator::detail::operator_minus(d), iter.get());
    }
    
    template<class... Iterator>
    constexpr mk2::iterator::tuple_iterator<Iterator...> operator-(
        const mk2::iterator::tuple_iterator<Iterator...> &lhv,
        const mk2::iterator::tuple_iterator<Iterator...> &rhv)
    {
        return mk2::iterator::detail::make_original_tuple_minus(lhv.get(), rhv.get());
    }
    
    template<class... Iterator>
    constexpr auto make_tuple_iterator(Iterator&&... args)
    {
        return tuple_iterator<Iterator...>{std::forward<Iterator>(args)...};
    }
    
    template<class... Container>
    class tuple_iterator_container_wrapper
    {
    public:
        using iterator          = tuple_iterator<typename mk2::container::container_traits<std::remove_reference_t<Container>>::iterator...>;
        using const_iterator    = const iterator;
        
        tuple_iterator_container_wrapper(Container&&... args) :
            begin_{make_tuple_iterator(std::begin(args)...)},
            end_{make_tuple_iterator(std::end(args)...)} {}
    
        iterator        begin() { return begin_; }
        const_iterator  begin() const { return begin_; }
        iterator        end() { return end_; }
        const_iterator  end() const { return end_; }
        const_iterator  cbegin() const { return begin_; }
        const_iterator  cend() const { return end_; }
        
    private:
        iterator begin_;
        iterator end_;
    };
    
    template<class... Container>
    constexpr auto make_tuple_iterator_container_wrapper(Container&&... args)
    {
        return tuple_iterator_container_wrapper<Container...>{std::forward<Container>(args)...};
    }
}
}

