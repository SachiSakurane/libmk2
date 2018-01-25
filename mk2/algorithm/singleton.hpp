//
// Created by Himatya on 2018/01/25.
//

#ifndef LIBMK2_ALGORITHM_SINGLETON_HPP
#define LIBMK2_ALGORITHM_SINGLETON_HPP

#include <memory>

namespace mk2{
namespace algorithm{
    template <typename _T>
    class singleton
    {
        
    public:
        static _T& instance()
        {
            static typename _T::singleton_pointer_type i(_T::create_instance());
            return get_reference(i);
        }
        
    private:
        typedef std::unique_ptr<_T> singleton_pointer_type;
        
        inline static _T *create_instance(){return new _T();}
        
        inline static _T &get_reference(const singleton_pointer_type &ptr){return *ptr;}
        
    protected:
        singleton(){}
        
    private:
        singleton(const singleton &) = delete;
        singleton& operator=(const singleton &) = delete;
        singleton(singleton &&) = delete;
        singleton& operator=(singleton &&) = delete;
    };
}
}

#endif