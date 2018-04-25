//
// Created by Himatya on 2018/04/25.
//

#ifndef LIBMK2_FILESYSTEM_GLOB_HPP
#define LIBMK2_FILESYSTEM_GLOB_HPP

#include <algorithm>
#include <string>
#include <vector>
#include <regex>

#include <mk2/filesystem/config.hpp>
#include <mk2/filesystem/path.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/range/iterator_range.hpp>

namespace mk2 {
namespace filesystem {

    namespace detail{
        template<class Char>
        auto glob_to_regex(const std::basic_string<Char>& s)
        {
            std::basic_string<Char> result;
            for (auto c = s.begin(); c != s.end(); ++c)
            {
                switch(*c)
                {
                    case mk2::string::ctot<Char>('*', L'*'):
                        result.push_back(mk2::string::ctot<Char>('.', L'.'));
                        result.push_back(*c);
                        break;

                    case mk2::string::ctot<Char>('?', L'?'):
                        result.push_back(mk2::string::ctot<Char>('.', L'.'));
                        break;

                    case mk2::string::ctot<Char>('[', L'['):
                        result.push_back(mk2::string::ctot<Char>('.', L'.'));
                        result.push_back(*c);
                        break;

                    case mk2::string::ctot<Char>('!', L'!'):
                        result.push_back(mk2::string::ctot<Char>('^', L'^'));
                        break;

                    case mk2::string::ctot<Char>('\\', L'\\'):
                        result.push_back(*c);
                        ++c;
                        result.push_back(*c);
                        break;

                    default:
                        result.push_back(*c);
                        break;

                }
            }

            return result;
        }

        template<class Char>
        auto find_glob_char(const std::basic_string<Char>& s)
        {
            return s.find_first_of(mk2::string::stot<Char>("*?[]!", L"*?[]!"));
        }

        template<class Char, class Iter>
        void glob_impl_1(
                const Iter& bread_crumbs_iter,
                const Iter& bread_crumbs_iter_end,
                const std::basic_string<Char>& path,
                std::vector<std::basic_string<Char>>& result)
        {
            const auto next = [bread_crumbs_iter](){ return ++bread_crumbs_iter; }();

            if(mk2::filesystem::detail::find_glob_char(*bread_crumbs_iter))
            {
                auto filter = std::regex(mk2::filesystem::detail::glob_to_regex(*bread_crumbs_iter));

                //glob表現が見つかった場合、派生で捜査する
                //nextがendならresultに突っ込む
                for (auto &&candidacy : boost::make_iterator_range(using_fs::directory_iterator(path),
                                                                   using_fs::directory_iterator()))
                {
                    if(std::regex_match(mk2::filesystem::get_string(candidacy.path()), filter))
                    {
                        glob_impl_1(next,
                                    bread_crumbs_iter_end,
                                    path + mk2::string::stot<Char>("/", L"/") + *bread_crumbs_iter,
                                    result);
                    }
                }
            }

            if(next != bread_crumbs_iter_end)
            {
                auto next_path = path + mk2::string::stot<Char>("/", L"/") + *bread_crumbs_iter;
                if(using_fs::exists(next_path))
                {
                    glob_impl_1(next,
                                bread_crumbs_iter_end,
                                next_path,
                                result);
                }
            }
            else
            {
                auto next_path = path + *bread_crumbs_iter;
                if(using_fs::exists(next_path))
                    result.emplace_back(next_path);
            }
        }

        template<class Char>
        auto glob_impl(const std::basic_string<Char>& path)
        {
            std::vector<std::basic_string<Char>> result;

            std::vector<std::string> bread_crumbs;
            boost::split(bread_crumbs, path, boost::is_any_of(mk2::string::stot<Char>("/", L"/")));

            if(!bread_crumbs.empty())
            {
                glob_impl_1(std::begin(bread_crumbs), std::end(bread_crumbs), mk2::string::stot<Char>("", L""), result);
            }

            return result;
        }
    }

    // なぜpathではなくstringかというと、もしglob文字が入っていた場合pathだと文字として検索してしまうため
    template<class Char>
    std::vector<std::basic_string<Char>> glob(const std::basic_string<Char>& path, bool is_recursive = false)
    {
        return mk2::filesystem::detail::glob_impl(path);
    }

}
}

#endif //LIBMK2_FILESYSTEM_GLOB_HPP
