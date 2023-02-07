#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include <string>
#include <algorithm>

int main()
{
    const std::filesystem::path fs {"/usr/include/c++/12/bits/fs_path.h"};

    if (std::filesystem::exists (fs)) {
        std::cout << "fs.cpp exist\n";
    }

    std::cout << "canonical file name: " << std::filesystem::canonical (fs).string () << '\n';
    std::cout << "file name: " << fs.filename ().string () << '\n';
    std::cout << "root name: " << fs.root_name ().string () << '\n';
    std::cout << "root directory: " << fs.root_directory ().string () << '\n';
    std::cout << "root path: " << fs.root_path ().string () << '\n';
    std::cout << "relative_path: " << fs.relative_path ().string () << '\n';
    std::cout << "parent_path: " << fs.parent_path ().string () << '\n';
    std::cout << "stem: " << fs.stem ().string () << '\n';
    std::cout << "extension: " << fs.extension ().string () << '\n';
    std::cout << "file size: " << std::filesystem::file_size (fs) << '\n';
    /// std::cout << ": " << fs.().string () << '\n';

    std::filesystem::path fs2 {"/tmp/"};
    auto fs3 = fs2 / std::filesystem::path {"01.cpp"};
    std::cout << "file name: /" << fs3.relative_path ().string () << '\n';

    std::cout << "hash: " << std::hash<std::filesystem::path> () (fs3) << std::endl;

    /// 遍历目录
    auto dir_iter = std::filesystem::directory_iterator ("/tmp/");
    for (auto& iter : dir_iter) {
        std::cout << iter.path ().string () << '\n';
    }
}
