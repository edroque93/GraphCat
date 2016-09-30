#include "stringops.hpp"

#include <algorithm>
#include <locale>
#include <vector>

using namespace std;

template <>
double str_as(const std::string &str) {
    return stod(str);
}

template <>
int str_as(const std::string &str) {
    return stoi(str);
}

template <>
string str_as(const std::string &str) {
    return str;
}

template <>
bool str_as(const std::string &str) {
    const static vector<string> yes = {"yes", "y", "true", "t", "1"};
    const static vector<string> no = {"no", "n", "false", "f", "0"};

    // TODO convert str to lower case

    if (find(yes.begin(), yes.end(), str) != yes.end()) return true;
    if (find(no.begin(), no.end(), str) != no.end()) return false;

    throw std::runtime_error(str + " is not a boolean value");
}
