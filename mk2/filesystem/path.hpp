//
// Created by Himatya on 2018/04/25.
//

#ifndef LIBMK2_PATH_HPP
#define LIBMK2_PATH_HPP

#include <string>

#include <mk2/string/convert.hpp>

namespace mk2 {
namespace filesystem {

    namespace detail {
        template<class Char, class Path>
        struct get_path_string
        {
            const Path& p_;

            explicit get_path_string(const Path& p) : p_(p){}

            auto operator()() const {return p_.string();}
        };

        template<class Path>
        struct get_path_string<wchar_t, Path>
        {
            const Path& p_;

            explicit get_path_string(const Path& p) : p_(p){}

            auto operator()() const {return p_.wstring();}
        };
    }

    template<class Char>
    bool is_absolute(const std::basic_string<Char>& path)
    {
        if(path.empty())
            return false;

        return path.find(mk2::string::stot<Char>("/", L"/")) == 0;
    }

    template<class Char, class Path>
    auto get_string(const Path& path)
    {
        return mk2::filesystem::detail::get_path_string<Char, Path>{path}();
    }

}
}

#endif //LIBMK2_PATH_HPP
