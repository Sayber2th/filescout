#include <algorithm>
#include <iostream>
#include <filesystem>
#include <vector>
#include <cstdlib>

namespace fs = std::filesystem;

static void check_user_syntax_error(const int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Wrong syntax used, please refer to the following\n"
        << "Usage: " << argv[0] << " <folder path>\n";
        std::exit(1);
    }
}

static void check_incorrect_path_provided(const fs::path& target_directory, std::error_code& ec)
{
    const bool is_dir = fs::is_directory(target_directory, ec);
    if (!is_dir)
    {
        if (ec)
        {
            std::cerr << "The specified directory cannot be accessed\n"
            << "Please review your specified path: " << target_directory.string() << '\n'
            << ec.message() << '\n';
            std::exit(1);
        }
        std::cerr << "The specified directory is not a directory\n"
        << "Please review your specified path: " << target_directory.string() << '\n';
        std::exit(1);
    }
}

static void custom_recursive_directory_iterator(const fs::path& folder_path, std::vector<fs::path>& unreadable_directories, std::vector<fs::path>& files_to_print)
{
    std::error_code ec;
    fs::directory_iterator iterator(folder_path, ec);
    if (ec)
    {
        unreadable_directories.push_back(folder_path);
        return;
    }

    for (const auto& entry : iterator)
    {
        if (entry.is_symlink())
        {
            continue;
        }

        if (entry.is_regular_file())
        {
            files_to_print.push_back(entry);
        }

        else if (entry.is_directory())
        {
            custom_recursive_directory_iterator(entry.path(), unreadable_directories, files_to_print);
        }
    }
}

static void print_printables(const std::vector<fs::path>& files_to_print, const std::vector<fs::path>& unreadable_directories)
{
    if (!files_to_print.empty())
    {
        for (const auto& entry : files_to_print)
        {
            std::cout << entry.string() << '\n';
        }
    }
    if (!unreadable_directories.empty())
    {
        std::cerr << "The following directories are not readable:\n";
        for (const auto &entry : unreadable_directories)
        {
            std::cerr << entry.string() << '\n';
        }
    }
}

int main(const int argc, char* argv[])
{
    check_user_syntax_error(argc, argv);

    fs::path target_directory = argv[1];
    std::error_code ec;

    check_incorrect_path_provided(target_directory, ec);

    std::vector<fs::path> files_to_print;
    std::vector<fs::path> unreadable_directories;

    custom_recursive_directory_iterator(target_directory, unreadable_directories, files_to_print);

    if (!files_to_print.empty()) std::ranges::sort(files_to_print);
    print_printables(files_to_print, unreadable_directories);

    return 0;
}