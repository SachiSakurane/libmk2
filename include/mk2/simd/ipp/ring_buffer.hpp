//
// Created by Himatya on 2018/08/12.
//

#pragma once

#include <mk2/container/fixed_array.hpp>
#include <mk2/container/container_traits.hpp>
#include <mk2/simd/ipp/function/arithmetic.hpp>
#include <mk2/simd/ipp/function/initialization.hpp>

namespace mk2 { namespace simd { namespace ipp
{
    // OperationFunc: f(Type bufptr, size index, int len, args...)
    namespace ring_buffer_operation
    {
        struct add
        {
            template <class Type>
            decltype(auto) operator()(Type* bufptr, size_t index, int len, const Type* src)
            {
                return function::add_inplace(src + index, bufptr, len);
            }

        };
    }

    template<class Type>
    class ring_buffer
    {
        using container_type = mk2::container::fixed_array<Type>;
        using size_type = typename mk2::container::container_traits<container_type>::size_type;
        
    public:
        explicit ring_buffer(size_type size) : size_(size), index_(0), container_(size) {}

        ring_buffer(size_type size, Type v) : size_(size), index_(0), container_(size, v) {}
        
        void set_sample(const Type* sample, size_t len)
        {
            auto data = container_.data();
            if (len + index_ < size_)
            {
                function::copy(sample, data + index_, static_cast<int>(len));
                index_ += len;
            }
            else if (len + index_ == size_)
            {
                function::copy(sample, data + index_, static_cast<int>(len));
                index_ = 0;
            }
            else if (len > size_)
            {
                auto pos = len - size_;
                function::copy(sample + pos, data, static_cast<int>(size_));
                index_ = 0;
            }
            else
            {
                auto section_size = size_ - index_;
                function::copy(sample, data + index_, static_cast<int>(section_size));
                index_ = len - section_size;
                function::copy(sample + section_size, data, static_cast<int>(index_));
            }
        }
        
        // OperationFunc: f(Type bufptr, size index, int len, args...)
        template<class OperationFunc, class ...Args>
        void operation(OperationFunc&& f, size_t len, Args&&... args)
        {
            auto data = container_.data();
            if (len + index_ < size_)
            {
                std::forward<OperationFunc>(f)(data + index_, 0, static_cast<int>(len), std::forward<Args>(args)...);
            }
            else
            {
                auto section_size = size_ - index_;
                std::forward<OperationFunc>(f)(data + index_, 0, static_cast<int>(section_size), std::forward<Args>(args)...);
                std::forward<OperationFunc>(f)(data, section_size, static_cast<int>(len - section_size), std::forward<Args>(args)...);
            }
        }
        
        decltype(auto) data() const { return container_.data(); }
        
        void copy_aligned_data(Type* dst, size_type size)
        {
            auto data = container_.data();
            if (size + index_ < size_)
            {
                function::copy(data + index_, dst, static_cast<int>(size));
            }
            else
            {
                auto section_size = size_ - index_;
                function::copy(data + index_, dst, static_cast<int>(section_size));
                function::copy(data, dst + section_size, static_cast<int>(size - section_size));
            }
        }

        void seek(size_t size)
        {
            index_ = (index_ + size) % size_;
        }
    
        auto size() const { return size_; }
        
    private:
        const std::size_t size_;
        size_type index_;
        container_type container_;
    };
}
}
}