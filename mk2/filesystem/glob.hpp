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
#include <mk2/iterator/select_iterator.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/range/iterator_range.hpp>

//TODO:相対パス

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
            return s.find_first_of(mk2::string::stot<Char>("*?[]!", L"*?[]!")) != std::basic_string<Char>::npos;
        }

        template<class Char, class Iter>
        void glob_impl_1(
                const Iter& bread_crumbs_iter,
                const Iter& bread_crumbs_iter_end,
                const std::basic_string<Char>& path,
                std::vector<std::basic_string<Char>>& result)
        {
            Iter copy_bread_crumbs_iter = bread_crumbs_iter;
            const auto next = [&](){ return ++copy_bread_crumbs_iter; }();
            const auto bread_crumbs = *bread_crumbs_iter;

            //glob表現が見つかった場合、派生先を再帰して捜査する
            if(mk2::filesystem::detail::find_glob_char(bread_crumbs))
            {
                auto filter = std::regex(mk2::filesystem::detail::glob_to_regex(path + bread_crumbs));

                for (auto &&candidacy : boost::make_iterator_range(mk2::filesystem::using_fs::directory_iterator{mk2::filesystem::using_fs::path{path + mk2::string::stot<Char>("/", L"/")}},
                                                                   mk2::filesystem::using_fs::directory_iterator{}))
                {
                    auto candidacy_path = mk2::filesystem::get_string<Char>(candidacy.path());

                    if(std::regex_match(candidacy_path, filter))
                    {
                        if(next != bread_crumbs_iter_end)
                        {
                            glob_impl_1(next, bread_crumbs_iter_end, candidacy_path + mk2::string::stot<Char>("/", L"/"), result);
                        }
                        else
                        {
                            result.emplace_back(candidacy_path);
                        }
                    }
                }
            }

            if(next != bread_crumbs_iter_end)
            {
                auto next_path = path + bread_crumbs + mk2::string::stot<Char>("/", L"/");
                if(mk2::filesystem::using_fs::exists(next_path))
                {
                    glob_impl_1(next, bread_crumbs_iter_end, next_path, result);
                }
            }
            else
            {
                auto next_path = path + bread_crumbs;
                if(mk2::filesystem::using_fs::exists(next_path))
                    result.emplace_back(next_path);
            }
        }

        template<class Char>
        auto glob_impl(const std::basic_string<Char>& path)
        {
            std::vector<std::basic_string<Char>> result;

            std::vector<std::basic_string<Char>> bread_crumbs;
            boost::split(bread_crumbs, path, boost::is_any_of(mk2::string::stot<Char>("/", L"/")));

            if(!bread_crumbs.empty())
            {
                glob_impl_1(std::begin(bread_crumbs), std::end(bread_crumbs), mk2::string::stot<Char>("", L""), result);
            }

            return result;
        }
    }

    // glob文字が入っていた場合pathだと文字として検索してしまうため、pathではなくstringを用いる
    template<class Char>
    std::vector<std::basic_string<Char>> glob(const std::basic_string<Char>& path, bool is_recursive = false)
    {
        auto absolute_path = path;
        if(!mk2::filesystem::is_absolute(path))
        {
            auto current_path = mk2::filesystem::using_fs::current_path();

            auto transform = [](const using_fs::path& path) { return mk2::filesystem::get_string<Char>(path); };

            namespace mk2iter = mk2::iterator;
            auto begin = mk2iter::make_select_iterator(std::begin(current_path), transform);
            std::vector<std::basic_string<Char>> current_crumbs{begin, begin.clone(std::end(current_path))};

            std::vector<std::basic_string<Char>> bread_crumbs;
            boost::split(bread_crumbs, path, boost::is_any_of(mk2::string::stot<Char>("/", L"/")));

            for (auto &&item : bread_crumbs)
            {
                if(item == mk2::string::stot<Char>(".", L"."))
                {
                }
                else if(item == mk2::string::stot<Char>("..", L".."))
                {
                    current_crumbs.erase(--std::end(current_crumbs));
                }
                else
                {
                    current_crumbs.emplace_back(item);
                }
            }

            if(current_crumbs.empty())
            {
                return {};
            }

            absolute_path = mk2::string::stot<Char>("", L"");
            for (auto item = ++current_crumbs.begin(); item != current_crumbs.end(); ++item)
            {
                absolute_path += mk2::string::stot<Char>("/", L"/") + *item;
            }
        }
        return mk2::filesystem::detail::glob_impl(absolute_path);
    }

}
}

#endif //LIBMK2_FILESYSTEM_GLOB_HPP
