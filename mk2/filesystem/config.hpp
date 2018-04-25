//
// Created by Himatya on 2018/04/25.
//

#ifndef LIBMK2_FILESYSTEM_CONFIG_HPP
#define LIBMK2_FILESYSTEM_CONFIG_HPP

#if defined(LIBMK2_FILESYSTEM_USING_BOOST) || __cplusplus < 201703L
#   include <boost/filesystem.hpp>
#   ifndef LIBMK2_FILESYSTEM_USING_BOOST
#       define LIBMK2_FILESYSTEM_USING_BOOST
#elif __has_include(<filesystem>)
#   include <filesystem>
#   define LIBMK2_FILESYSTEM_INCLUDED_FILESYSTEM
#else
#   include <experimental/filesystem>
#   define LIBMK2_FILESYSTEM_INCLUDED_EXPERIMENTAL_FILESYSTEM
#endif

namespace mk2 {
namespace filesystem {
#if defined(LIBMK2_FILESYSTEM_USING_BOOST)
    namespace using_fs = boost::filesystem;
#elif defined(LIBMK2_FILESYSTEM_INCLUDED_FILESYSTEM)
    namespace using_fs = std::filesystem;
#elif defined(LIBMK2_FILESYSTEM_INCLUDED_EXPERIMENTAL_FILESYSTEM)
    namespace using_fs = std::experimental::filesystem;
#endif

}
}

#endif //LIBMK2_FILESYSTEM_CONFIG_HPP
