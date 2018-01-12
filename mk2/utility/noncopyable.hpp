//
// Created by Himatya on 2018/01/12.
//

#ifndef LIBMK2_UTILITY_NONCOPYABLE_HPP
#define LIBMK2_UTILITY_NONCOPYABLE_HPP

namespace mk2{
namespace utility{

    template<typename T>
    class noncopyable
    {
    protected:
        noncopyable() {}
        ~noncopyable() {}
    private:
        noncopyable(const noncopyable &) = delete;
        noncopyable& operator=(const noncopyable &) = delete;
    };

}
}

#endif