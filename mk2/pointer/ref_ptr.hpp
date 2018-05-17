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
        typedef Type element_type;

        ref_ptr() : elem_(nullptr) {}

        ref_ptr(std::nullptr_t) : elem_(nullptr) {}

        template<typename Type2>
        ref_ptr(const ref_ptr<Type2>& obj) : elem_(obj.elem_) {}

        template<typename Type2>
        ref_ptr(ref_ptr<Type2>&& obj) : elem_(obj.elem_)
        {
            obj.elem_ = nullptr;
        }

        template<typename Type2>
        explicit ref_ptr(Type2* ptr) : elem_(ptr) {}

        template<typename SmartPointer>
        explicit ref_ptr(const SmartPointer& ptr) : elem_(ptr.get()) {}

        template<typename Type2>
        ref_ptr& operator=(const ref_ptr<Type2>& ptr)
        {
            this->elem_ = ptr.elem_;
            return *this;
        }

        template<typename Type2>
        ref_ptr& operator=(ref_ptr<Type2>&& ptr)
        {
            this->elem_ = ptr.elem_;
            ptr.elem_ = nullptr;
            return *this;
        }

        template<typename Type2>
        ref_ptr& operator=(Type2* ptr)
        {
            this->elem_ = ptr;
            return *this;
        }

        template<typename SmartPointer>
        ref_ptr& operator=(const SmartPointer& ptr)
        {
            this->elem_ = ptr.get();
            return *this;
        }

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

    template<class T, class U>
    bool operator==(const ref_ptr<T>& lhv, const U& rhv)
    {
        return lhv.get() == rhv.get();
    }

    template<class T, class U>
    bool operator==(const T& lhv, const ref_ptr<U>& rhv)
    {
        return lhv.get() == rhv.get();
    }

    template<class T, class U>
    bool operator==(const ref_ptr<T>& lhv, const U* rhv)
    {
        return lhv.get() == rhv;
    }

    template<class T, class U>
    bool operator==(const T* lhv, const ref_ptr<U>& rhv)
    {
        return lhv == rhv.get();
    }

    template<class T, class U>
    bool operator!=(const ref_ptr<T>& lhv, const U& rhv)
    {
        return !(lhv == rhv);
    }

    template<class T, class U>
    bool operator!=(const T& lhv, const ref_ptr<U>& rhv)
    {
        return !(lhv == rhv);
    }

    template<class T, class U>
    bool operator!=(const ref_ptr<T>& lhv, const U* rhv)
    {
        return !(lhv == rhv);
    }

    template<class T, class U>
    bool operator!=(const T* lhv, const ref_ptr<U>& rhv)
    {
        return !(lhv == rhv);
    }
    
    template<class Type>
    ref_ptr<Type> make_ref_ptr(Type* p)
    {
        return ref_ptr<Type>(p);
    }
    
    template<class SmartPointer>
    ref_ptr<typename std::pointer_traits<SmartPointer>::element_type> make_ref_ptr(const SmartPointer& p)
    {
        return ref_ptr<typename std::pointer_traits<SmartPointer>::element_type>(p.get());
    }
}
}

#endif //LIBMK2_REF_PTR_HPP
