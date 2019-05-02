//
// Created by Himatya on 2019-03-26.
//

#include <ctime>
#include <iomanip>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

void make_include_file(const std::filesystem::path& path, const std::string& root, const std::string& time_stamp)
{
    auto file_name = path.string() + ".hpp";
    std::ofstream ofs(file_name);
    ofs.clear();

    ofs << "//" << std::endl;
    ofs << "// Created by SachiSakurane on " << time_stamp << "." << std::endl;
    ofs << "//" << std::endl;
    ofs << std::endl;
    ofs << "#pragma once" << std::endl;
    ofs << std::endl;

    // ファイル作るだけ
    for (auto&& item : std::filesystem::directory_iterator(path))
    {
        if (item.path().filename().string().front() == '.')
            continue;

        if (item.is_directory())
        {
            make_include_file(item.path(), root + item.path().filename().string() + "/", time_stamp);
        }
    }

    std::cout << path << std::endl;

    // 書き込み
    for (auto&& item : std::filesystem::directory_iterator(path))
    {
        if (item.path().filename().string().front() == '.')
            continue;

        if (item.is_regular_file() && item.path().extension() == ".hpp")
        {
            std::cout << "#include <" << root << item.path().filename().string() << ">" << std::endl;
            ofs << "#include <" << root << item.path().filename().string() << ">" << std::endl;
        }
    }

    ofs << std::endl;
    std::cout << std::endl;
}

int main(const int argc, const char** argv)
{
    if (argc > 1)
    {
        time_t now = std::time(nullptr);
        struct tm* local_now = std::localtime(&now);

        std::stringstream ss;
        ss << (local_now->tm_year + 1900) << "-" << std::setfill('0') << std::setw(2) << local_now->tm_mon + 1 << "-" << local_now->tm_mday;

        auto path = std::filesystem::path(std::filesystem::path{argv[1]});
        make_include_file(path, path.filename().string() + "/", ss.str());

    }
    else
    {
        std::cout << "must be write library include path at 1st arg" << std::endl;
    }

    return 0;
}
