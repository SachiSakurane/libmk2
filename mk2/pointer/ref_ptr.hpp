//
// Created by Himatya on 2017/12/13.
//

#ifndef LIBMK2_REF_PTR_HPP
#define LIBMK2_REF_PTR_HPP

#include <memory>

namespace mk2 {
namespace pointer{
    template<typename Type>
    class ref_ptr
    {
    public:
        typedef Type* pointer;
        typedef Type& reference;

        ref_ptr() : elem_(nullptr)
        {}

        explicit ref_ptr(pointer ptr) : elem_(ptr)
        {}

        explicit ref_ptr(const std::unique_ptr<Type> &ptr) : elem_(ptr.get())
        {}

        pointer get() const
        {
            return elem_;
        }

        pointer operator->() const
        {
            return elem_;
        }

        reference operator*() const
        {
            return *elem_;
        }

        explicit operator bool() const
        {
            return elem_ != nullptr;
        }

        void reset(pointer p = pointer())
        {
            elem_ = p;
        }

        pointer release()
        {
            elem_ = nullptr;
        }

    private:
        Type *elem_;
    };
}
}

#endif //LIBMK2_REF_PTR_HPP
