#pragma once

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

namespace Utils {
    void Error(const std::string& s);

    bool EndsWith(const std::string& haystack, const std::string& needle);

    std::vector<std::string> GetFilesInDirectory(const char* directory);
    std::vector<std::string> SplitString(std::string str, const char* delimiter);
}

#endif // !UTILS_HPP
