#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "stringops.hpp"

struct option_desc {
    std::string label;
    std::string help;
    std::string value;
};

class option_list {
    std::vector<option_desc> opts;

    std::vector<option_desc>::iterator find(const std::string &lab);

   public:
    option_list() {}
    option_list(std::initializer_list<option_desc> opt_list) : opts(opt_list) {}

    const std::string &operator[](const std::string &lab);
    bool is_set(const std::string &lab);

    template <class T>
    T get(const std::string &lab) {
        auto it = find(lab);
        if (it->value.empty()) {
            throw std::runtime_error("option -" + lab + " has no value");
        }
        return str_as<T>(it->value);
    }

    template <class T>
    std::vector<T> get_all(const std::string &lab) {
        auto it = find(lab);
        const std::string &line = it->value;
        return str_split<T>(line, ",; ");
    }

    void show_help(std::ostream &os = std::cout);
    int parse(int argc, char **argv);
};
