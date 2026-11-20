#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main(const int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Wrong syntax used, please refer to the following\n"
        << "Usage: " << argv[0] << " <folder path>\n";
        return 1;
    }

    const fs::path target_directory = argv[1];
    std::error_code ec;
    const bool is_dir = fs::is_directory(target_directory, ec);
    if (!is_dir)
    {
        if (ec)
        {
            std::cerr << "The specified directory cannot be accessed\n"
            << "Please review your specified path: " << target_directory.string() << '\n'
            << ec.message() << '\n';
            return 1;
        }
        std::cerr << "The specified directory is not a directory\n"
        << "Please review your specified path: " << target_directory.string() << '\n';
        return 1;
    }

    for (const auto &entry : fs::recursive_directory_iterator(target_directory, fs::directory_options::skip_permission_denied))
    {
        if (entry.is_regular_file())
        {
            std::cout << entry.path().string() << '\n';
        }
    }
    return 0;
}