//
// Created by Himatya on 2017/12/04.
//

#ifndef LIBMK2_ITERATOR_INDEX_ITERATOR_HPP
#define LIBMK2_ITERATOR_INDEX_ITERATOR_HPP

#include <cstddef>
#include <iterator>

namespace mk2{
namespace iterator{

    template<class Container>
    class index_iterator
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = typename Container::value_type;
        using difference_type   = size_t;
        using pointer           = typename Container::pointer;
        using reference         = typename Container::reference;

        constexpr index_iterator(Container &c, std::size_t index = 0u) : container_(c), index_(index){}

        constexpr index_iterator(const index_iterator& obj) : container_(obj.container_), index_(obj.index_){}
        constexpr index_iterator(index_iterator&& obj) : container_(obj.container_), index_(obj.index_){}
    
        index_iterator& operator=(const index_iterator& obj)
        {
            this->container_ = obj.container_;
            this->index_ = obj.index_;
            return *this;
        }
    
        index_iterator& operator=(index_iterator&& obj)
        {
            this->container_ = std::move(obj.container_);
            this->index_ = std::move(obj.index_);
            return *this;
        }
        
        constexpr auto operator *() -> decltype(auto)
        {
            return container_[index_];
        }

        constexpr auto operator *() const -> decltype(auto)
        {
            return container_[index_];
        }

        constexpr auto operator ->() -> decltype(auto)
        {
            return &container_[index_];
        }

        constexpr auto operator ->() const -> decltype(auto)
        {
            return &container_[index_];
        }

        constexpr auto operator[](difference_type rhv) -> decltype(auto)
        {
            return container_[index_ + rhv];
        }

        constexpr auto operator[](difference_type rhv) const -> decltype(auto)
        {
            return container_[index_ + rhv];
        }

        constexpr index_iterator& operator ++()
        {
            ++index_;
            return *this;
        }

        constexpr index_iterator& operator --()
        {
            --index_;
            return *this;
        }

        constexpr index_iterator operator ++(int)
        {
            index_iterator t = *this;
            ++t.index_;
            return t;
        }

        constexpr index_iterator operator --(int)
        {
            index_iterator t = *this;
            --t.index_;
            return t;
        }

        constexpr index_iterator& operator +=(difference_type rhv)
        {
            index_ += rhv;
            return *this;
        }

        constexpr index_iterator& operator -=(difference_type rhv)
        {
            index_ -= rhv;
            return *this;
        }

        template<class Item>
        friend constexpr index_iterator<Item> operator+(const index_iterator<Item>&, typename Item::difference_type);

        template<class Item>
        friend constexpr index_iterator<Item> operator+(typename Item::difference_type, const index_iterator<Item>&);

        template<class Item>
        friend constexpr index_iterator<Item> operator-(const index_iterator<Item>&, typename Item::difference_type);

        template<class Item>
        friend constexpr typename Item::difference_type operator-(const index_iterator<Item>&, const index_iterator<Item>&);

        template<class Item>
        friend constexpr bool operator==(const index_iterator<Item>&, const index_iterator<Item>&);

        template<class Item>
        friend constexpr bool operator!=(const index_iterator<Item>&, const index_iterator<Item>&);

        template<class Item>
        friend constexpr bool operator< (const index_iterator<Item>&, const index_iterator<Item>&);

        template<class Item>
        friend constexpr bool operator<=(const index_iterator<Item>&, const index_iterator<Item>&);

        template<class Item>
        friend constexpr bool operator> (const index_iterator<Item>&, const index_iterator<Item>&);

        template<class Item>
        friend constexpr bool operator>=(const index_iterator<Item>&, const index_iterator<Item>&);

        template<class Item>
        friend constexpr void swap(index_iterator<Item>&, index_iterator<Item>&);

    private:
        Container& container_;
        difference_type index_;
    };

    template<class Item>
    constexpr index_iterator<Item> operator+(const index_iterator<Item>& lhv, typename Item::difference_type rhv)
    {
        return index_iterator<Item>(lhv.container_, lhv.index_ + rhv);
    }

    template<class Item>
    constexpr index_iterator<Item> operator+(typename Item::difference_type lhv, const index_iterator<Item>& rhv)
    {
        return index_iterator<Item>(rhv.container_, lhv + rhv.index_);
    }

    template<class Item>
    constexpr index_iterator<Item> operator-(const index_iterator<Item>& lhv, typename Item::difference_type rhv)
    {
        return index_iterator<Item>(lhv.container_, lhv.index_ - rhv);
    }

    template<class Item>
    constexpr typename Item::difference_type operator-(const index_iterator<Item>& lhv, const index_iterator<Item>& rhv)
    {
        return lhv.index_ - rhv.index_;
    }

    template<class Item>
    constexpr bool operator==(const index_iterator<Item>& lhv, const index_iterator<Item>& rhv)
    {
        return &lhv.container_ == &rhv.container_ && lhv.index_ == rhv.index_;
    }

    template<class Item>
    constexpr bool operator!=(const index_iterator<Item>& lhv, const index_iterator<Item>& rhv)
    {
        return &lhv.container_ != &rhv.container_ || lhv.index_ != rhv.index_;
    }

    template<class Item>
    constexpr bool operator< (const index_iterator<Item>& lhv, const index_iterator<Item>& rhv)
    {
        return lhv.index_ < rhv.index_;
    }

    template<class Item>
    constexpr bool operator<=(const index_iterator<Item>& lhv, const index_iterator<Item>& rhv)
    {
        return lhv.index_ <= rhv.index_;
    }

    template<class Item>
    constexpr bool operator> (const index_iterator<Item>& lhv, const index_iterator<Item>& rhv)
    {
        return lhv.index_ > rhv.index_;
    }

    template<class Item>
    constexpr bool operator>=(const index_iterator<Item>& lhv, const index_iterator<Item>& rhv)
    {
        return lhv.index_ >= rhv.index_;
    }

    template<class Item>
    constexpr void swap(index_iterator<Item>& lhv, index_iterator<Item>& rhv)
    {
        index_iterator<Item> temp = lhv;
        lhv = rhv;
        rhv = temp;
    }
}
}

#endif //LIBMK2_INDEX_ITERATOR_HPP
