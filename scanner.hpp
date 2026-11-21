#ifndef FILESCOUT_SCANNER_HPP
#define FILESCOUT_SCANNER_HPP

#include <vector>
#include <filesystem>
#include <system_error>

struct scanned_items
{
    std::vector<std::filesystem::path> files;
    std::vector<std::filesystem::path> unreadable_directories;
};

scanned_items scan_directory(const std::filesystem::path& target_directory, std::error_code& ec);

#endif //FILESCOUT_SCANNER_HPP