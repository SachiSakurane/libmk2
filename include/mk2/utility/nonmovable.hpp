//
// Created by Himatya on 2018/01/12.
//

#ifndef LIBMK2_UTILITY_NONMOVEABLE_HPP
#define LIBMK2_UTILITY_NONMOVEABLE_HPP

namespace mk2{
namespace utility{

    template<typename T>
    class nonmovable
    {
    protected:
        nonmovable() {}
        ~nonmovable() {}
    private:
        nonmovable(nonmovable &&) = delete;
        nonmovable& operator=(nonmovable &&) = delete;
    };

}
}

#endif