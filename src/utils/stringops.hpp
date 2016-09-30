#pragma once

#include <string>
#include <vector>

template <class T>
T str_as(const std::string &str);

template <class T>
std::vector<T> str_split(const std::string &str,
                         const std::string &delim = ",; ") {
    std::vector<T> vec;
    std::string::size_type last_pos = str.find_first_not_of(delim, 0);
    std::string::size_type pos = str.find_first_of(delim, last_pos);

    while (std::string::npos != pos || std::string::npos != last_pos) {
        std::string sub = str.substr(last_pos, pos - last_pos);
        vec.push_back(str_as<T>(sub));

        last_pos = str.find_first_not_of(delim, pos);
        pos = str.find_first_of(delim, last_pos);
    }

    return vec;
}
