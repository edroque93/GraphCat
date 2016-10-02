#include "stringops.hpp"

#include <algorithm>
#include <locale>
#include <vector>

using namespace std;

template <>
double str_as(const string &str) {
    return stod(str);
}

template <>
int str_as(const string &str) {
    return stoi(str);
}

template <>
string str_as(const string &str) {
    return str;
}

template <>
char str_as(const string &str) {
    if (str.empty()) throw runtime_error("string is empty");
    if (str.size() > 1) throw runtime_error("string is not a character");
    return str.front();
}

template <>
bool str_as(const string &str) {
    const static vector<string> yes = {"yes", "y", "true", "t", "1"};
    const static vector<string> no = {"no", "n", "false", "f", "0"};

    // TODO convert str to lower case

    if (find(yes.begin(), yes.end(), str) != yes.end()) return true;
    if (find(no.begin(), no.end(), str) != no.end()) return false;

    throw runtime_error(str + " is not a boolean value");
}
