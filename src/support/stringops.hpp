#ifndef STRINGOPS_HPP
#define STRINGOPS_HPP

#include <string>
#include <vector>

void str_tolower(std::string &);
void str_toupper(std::string &);

void str_rtrim(std::string &);
void str_ltrim(std::string &);
void str_trim(std::string &);

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

    return std::move(vec);
}

#endif // STRINGOPS_HPP
