//
// Created by Himatya on 2018/04/25.
//

#ifndef LIBMK2_CONVERT_HPP
#define LIBMK2_CONVERT_HPP

#include <string>
#include <type_traits>
#include <utility>

namespace mk2 {
namespace string {

    namespace detail{
        template<class Char>
        struct str_dist
        {
            std::string s_;

            str_dist(const std::string& s, const std::wstring&) : s_(s){}

            auto operator()() const { return s_; }
        };

        template<>
        struct str_dist<wchar_t>
        {
            std::wstring s_;

            str_dist(const std::string&, const std::wstring& ws) : s_(ws){}

            auto operator()() const { return s_; }
        };

        template<class Char>
        struct char_dist
        {
            char c_;

            constexpr char_dist(char c, wchar_t) : c_(c){}

            constexpr auto operator()() const { return c_; }
        };

        template<>
        struct char_dist<wchar_t>
        {
            wchar_t c_;

            constexpr char_dist(char, wchar_t c) : c_(c){}

            constexpr auto operator()() const { return c_; }
        };
    }

    template<typename Char>
    std::basic_string<Char> stot(const std::string& s, const std::wstring& ws)
    {
        return mk2::string::detail::str_dist<Char>(s, ws)();
    }

    template<typename Char>
    constexpr Char ctot(char s, wchar_t ws)
    {
        return mk2::string::detail::char_dist<Char>(s, ws)();
    }

}
}

#endif //LIBMK2_CONVERT_HPP
