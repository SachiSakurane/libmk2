//
// Created by Himatya on 2018/08/12.
//

#pragma once

#include <mk2/container/fixed_array.hpp>
#include <mk2/container/container_traits.hpp>
#include <mk2/simd/ipp/function/initialization.hpp>

namespace mk2 { namespace simd { namespace ipp
{
    template<class Type>
    class ring_buffer
    {
        using container_type = mk2::container::fixed_array<Type>;
        using size_type = typename mk2::container::container_traits<container_type>::size_type;
        
    public:
        ring_buffer(size_type size, Type v) : size_(size), index_(0), container_(size, v) {}
        
        void set(const Type* sample, size_type size)
        {
            auto data = container_.data();
            if (size + index_ < size_)
            {
                function::ipps_copy(sample, data + index_, static_cast<int>(size));
                index_ += size;
            }
            else if(size + index_ == size_)
            {
                function::ipps_copy(sample, data + index_, static_cast<int>(size));
                index_ = size;
            }
            else
            {
                auto section_size = size_ - index_;
                function::ipps_copy(sample, data + index_, static_cast<int>(section_size));
                index_ = size - section_size;
                function::ipps_copy(sample + section_size, data, static_cast<int>(index_));
            }
        }
        
        decltype(auto) data(){ return container_.data(); }
        
        void copy_aligned_data(Type* dst, size_type size)
        {
            auto data = container_.data();
            if (size + index_ < size_)
            {
                function::ipps_copy(data + index_, dst, static_cast<int>(size));
            }
            else
            {
                auto section_size = size_ - index_;
                function::ipps_copy(data + index_, dst, static_cast<int>(section_size));
                function::ipps_copy(data, dst + section_size, static_cast<int>(size - section_size));
            }
        }
    
    private:
        const std::size_t size_;
        size_type index_;
        container_type container_;
    };
}
}
}