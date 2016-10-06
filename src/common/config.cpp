#include "config.hpp"

#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>

#include "../utils/stringops.hpp"

using namespace std;

const string &config::section::operator[](const string &key) const {
    auto it = values.find(key);
    if (it == values.end()) throw runtime_error("value " + key + " not found");
    return it->second;
}

bool config::section::is_set(const string &key) const {
    auto it = values.find(key);
    return it != values.end();
}

config config::read_ini(const string &filename) {
    config cfg;
    ifstream ifs(filename);
    string line;

    std::map<std::string, std::string> *section = nullptr;
    size_t lineno = 0;

    while (getline(ifs, line)) {
        ++lineno;
        // remove comments
        line.erase(find_if(line.begin(), line.end(),
                           [](char c) { return c == ';' || c == '#'; }),
                   line.end());
        // trim whitespace
        str_trim(line);
        if (line.size() == 0) continue;
        if (line.front() == '[') {  // [section]
            if (line.back() != ']') {
                throw runtime_error("line " + to_string(lineno) +
                                    ": expected ']'");
            }
            string name = line.substr(1, line.size() - 2);
            str_trim(name);
            str_tolower(name);
            if (name.size() == 0) {
                throw runtime_error("line " + to_string(lineno) +
                                    ": expected identifier");
            }
            map<string, string> values;
            auto ret = cfg.values.insert(make_pair(name, values));
            if (ret.second == false) {
                throw runtime_error("line " + to_string(lineno) +
                                    ": duplicate section");
            }
            section = &(ret.first->second);
        } else {  // key = value
            if (section == nullptr) {
                throw runtime_error("line " + to_string(lineno) +
                                    ": no current section");
            }
            if (!isalpha(line.front())) {
                throw runtime_error("line " + to_string(lineno) +
                                    ": expected identifier");
            }
            auto pos = line.find('=');
            if (pos == string::npos) {
                throw runtime_error("line " + to_string(lineno) +
                                    ": missing '='");
            }
            string key = line.substr(0, pos);
            str_trim(key);
            str_tolower(key);
            string value = line.substr(pos + 1, line.size() - pos - 1);
            str_trim(value);
            if (value.size() == 0) {
                throw runtime_error("line " + to_string(lineno) +
                                    ": missing value");
            }
            auto ret = section->insert(make_pair(key, value));
            if (ret.second == false) {
                throw runtime_error("line " + to_string(lineno) +
                                    ": duplicate section");
            }
        }
    }
    return move(cfg);
}

void config::save_ini(const string &filename) {
    ofstream ofs(filename);
    for (const auto &sec : values) {
        ofs << '[' << sec.first << "]\n";
        for (const auto &p : sec.second) {
            ofs << p.first << " = " << p.second << '\n';
        }
    }
}

bool config::has_section(const string &name) const {
    auto it = values.find(name);
    return it != values.end();
}

config::section config::operator[](const string &name) const {
    auto it = values.find(name);
    if (it == values.end())
        throw runtime_error("section " + name + " not found");
    config::section sec(name, it->second);
    return move(sec);
}

ostream &operator<<(ostream &os, const config &cfg) {
    for (const auto &sec : cfg.values) {
        cout << " [" << sec.first << "]\n";
        for (const auto &p : sec.second) {
            cout << ' ' << p.first << " = " << p.second << '\n';
        }
    }
    return os;
}
