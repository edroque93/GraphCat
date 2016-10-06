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

    string key(str);
    str_tolower(key);

    if (find(yes.begin(), yes.end(), key) != yes.end()) return true;
    if (find(no.begin(), no.end(), key) != no.end()) return false;

    throw runtime_error(str + " is not a boolean value");
}

void str_tolower(string &str) {
    for (char &c : str) {
        c = tolower(c);
    }
}

void str_toupper(string &str) {
    for (char &c : str) {
        c = toupper(c);
    }
}

void str_ltrim(string &str) {
    str.erase(str.begin(), find_if(str.begin(), str.end(),
                                   not1(ptr_fun<int, int>(isspace))));
}

void str_rtrim(string &str) {
    str.erase(
        find_if(str.rbegin(), str.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        str.end());
}

void str_trim(string &str) {
    str_rtrim(str);
    str_ltrim(str);
}
