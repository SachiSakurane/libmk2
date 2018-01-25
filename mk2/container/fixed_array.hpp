//
// Created by Himatya on 2017/12/04.
//

#ifndef LIBMK2_CONTAINER_FIXED_ARRAY_HPP
#define LIBMK2_CONTAINER_FIXED_ARRAY_HPP

#include <iostream>
#include <memory>
#include <utility>
#include <tuple>

#include <mk2/iterator/index_iterator.hpp>

namespace mk2 { 
namespace container{

    struct tuple_construct_t{};
    constexpr tuple_construct_t tuple_construct = tuple_construct_t();

    template<typename Type, typename Allocator = std::allocator<Type>>
    class fixed_array {
    private:
        typedef fixed_array array;
        typedef std::allocator_traits<Allocator> allocator_traits;

    public:
        typedef Type value_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef mk2::iterator::index_iterator<array> iterator;
        typedef mk2::iterator::index_iterator<const array> const_iterator;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        explicit fixed_array(size_t size, const Allocator &a = Allocator());

        fixed_array(size_t size, const Type &value, const Allocator &a = Allocator());

        template<typename Tuple>
        fixed_array(size_t size, tuple_construct_t, Tuple&& tuple, const Allocator &a = Allocator());

        template<typename InputIter>
        fixed_array(InputIter first, InputIter last, const Allocator &a = Allocator());

        fixed_array(std::initializer_list<Type> il, const Allocator &a = Allocator());

        fixed_array(const fixed_array &);

        fixed_array(fixed_array &&) noexcept;

        fixed_array(const fixed_array &, const Allocator &a);

        fixed_array(fixed_array &&, const Allocator &a);

        ~fixed_array() {
            if (elems_) {
                destroy();
            }
        }

        fixed_array& operator=(const fixed_array& );

        fixed_array& operator=(fixed_array&& );

        iterator begin() noexcept { return iterator(*this, 0); }

        const_iterator begin() const noexcept { return const_iterator(*this, 0); }

        iterator end() noexcept { return iterator(*this, size_); }

        const_iterator end() const noexcept { return const_iterator(*this, size_); }

        reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

        const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }

        reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

        const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

        const_iterator cbegin() const noexcept { return begin(); }

        const_iterator cend() const noexcept { return end(); }

        const_reverse_iterator crbegin() const noexcept { return rbegin(); }

        const_reverse_iterator crend() const noexcept { return rend(); }

        size_type size() const noexcept { return size_; }

        size_type max_size() const noexcept { return size_; }

        bool empty() const noexcept { return size_ == 0; }

        reference operator[](size_t n) noexcept { return elems_[n]; }

        const_reference operator[](size_t n) const noexcept { return elems_[n]; }

        reference at(size_t n) noexcept {
            return n < size_ ? elems_[n] : throw std::out_of_range("array::at");
        }

        const_reference at(size_t n) const noexcept {
            return n < size_ ? elems_[n] : throw std::out_of_range("array::at");
        }

        reference front() noexcept { return elems_[0]; }

        const_reference front() const noexcept { return elems_[0]; }

        reference back() noexcept { return elems_[size_ > 0 ? size_ - 1 : 0]; }

        const_reference back() const noexcept { return elems_[size_ > 0 ? size_ - 1 : 0]; }

        value_type *data() noexcept { return elems_; }

        value_type *data() const noexcept { return elems_; }

    private:
        const size_type size_;
        Allocator allocator_;
        Type *elems_;

        template<typename Tuple, size_t... Indices>
        fixed_array(size_t size, Tuple&& tuple, const Allocator &a, std::index_sequence<Indices...>);

        void destroy() {
            allocator_traits::destroy(allocator_, elems_);
            allocator_traits::deallocate(allocator_, elems_, size_);
            elems_ = nullptr;
        }
    };

    template<typename Type, typename Allocator>
    fixed_array<Type, Allocator>::fixed_array(size_t size, const Allocator &a)
            : size_(size), allocator_(a), elems_(allocator_traits::allocate(allocator_, size_)) {
        Type *e = elems_;
        for (int i = 0; i < size_; ++i)
            allocator_traits::construct(allocator_, e++, Type());
    }

    template<typename Type, typename Allocator>
    fixed_array<Type, Allocator>::fixed_array(size_t size, const Type &value, const Allocator &a)
            : size_(size), allocator_(a), elems_(allocator_traits::allocate(allocator_, size_)) {
        Type *e = elems_;
        for (size_t i = 0; i < size_; ++i)
            allocator_traits::construct(allocator_, e++, value);
    }

    template<typename Type, typename Allocator>
    template<class Tuple>
    fixed_array<Type, Allocator>::fixed_array(size_t size, tuple_construct_t, Tuple&& tuple, const Allocator &a)
            : fixed_array(size, std::forward<Tuple>(tuple), a, std::make_index_sequence<std::tuple_size<Tuple>::value>()){
    }

    template<typename Type, typename Allocator>
    template<typename Tuple, size_t... Indices>
    fixed_array<Type, Allocator>::fixed_array(size_t size, Tuple&& tuple, const Allocator &a, std::index_sequence<Indices...>)
            : size_(size), allocator_(a), elems_(allocator_traits::allocate(allocator_, size_)) {
        Type *e = elems_;
        for (size_t i = 0; i < size_; ++i)
            allocator_traits::construct(allocator_, e++, std::get<Indices>(std::forward<Tuple>(tuple))...);
    }

    template<typename Type, typename Allocator>
    template<typename InputIter>
    fixed_array<Type, Allocator>::fixed_array(InputIter first, InputIter last, const Allocator &a)
            : size_((size_type)std::distance(first, last)), allocator_(a), elems_(allocator_traits::allocate(allocator_, size_)) {
        for (Type *e = elems_; first != last; ++first)
            allocator_traits::construct(allocator_, e++, *first);
    }

    template<typename Type, typename Allocator>
    fixed_array<Type, Allocator>::fixed_array(std::initializer_list<Type> il, const Allocator &a)
            : fixed_array(std::cbegin(il), std::cend(il), a) {}

    template<typename Type, typename Allocator>
    fixed_array<Type, Allocator>::fixed_array(const fixed_array &obj)
            : fixed_array(std::cbegin(obj), std::cend(obj), obj.allocator_) {}

    template<typename Type, typename Allocator>
    fixed_array<Type, Allocator>::fixed_array(fixed_array &&obj) noexcept
            : size_(std::move(obj.size_)), allocator_(std::move(obj.allocator_)), elems_(obj.elems_) {
        obj.elems_ = nullptr;
    }

    template<typename Type, typename Allocator>
    fixed_array<Type, Allocator>::fixed_array(const fixed_array &obj, const Allocator &a)
            : fixed_array(std::cbegin(obj), std::cend(obj), a) {}

    template<typename Type, typename Allocator>
    fixed_array<Type, Allocator>::fixed_array(fixed_array &&obj, const Allocator &a)
            : size_(std::move(obj.size_)), allocator_(a), elems_(obj.elems_) {
        obj.elems_ = nullptr;
    }

    template<typename Type, typename Allocator>
    fixed_array<Type, Allocator>& fixed_array<Type, Allocator>::operator=(const fixed_array& obj)
    {
        destroy();
        const_cast<size_type&>(this->size_) = obj.size_;
        this->allocator_ = obj.allocator_;
        this->elems_ = allocator_traits::allocate(allocator_, size_);
        Type *e = elems_;
        for (size_t i = 0; i < size_; ++i)
            allocator_traits::construct(allocator_, e++, obj[i]);
        return *this;
    }

    template<typename Type, typename Allocator>
    fixed_array<Type, Allocator>& fixed_array<Type, Allocator>::operator=(fixed_array&& obj)
    {
        const_cast<size_type&>(this->size_) = std::move(obj.size_);
        this->allocator_ = std::move(obj.allocator_);
        this->elems_ = obj.elems_;
        obj.elems_ = nullptr;
        return *this;
    }

}
}
#endif //LIBMK2_FIXED_ARRAY_HPP
