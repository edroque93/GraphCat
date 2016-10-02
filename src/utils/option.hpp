#pragma once

#include <iostream>
#include <stdexcept>
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

    const std::string &find(const std::string &lab) const;
    void set(const std::string &lab, const std::string &val);

   public:
    option_list() {}
    option_list(std::initializer_list<option_desc> opt_list) : opts(opt_list) {}

    const std::string &operator[](const std::string &lab) const;
    bool is_set(const std::string &lab) const;

    template <class T>
    T get(const std::string &lab) const {
        auto &val = find(lab);
        if (val.empty()) {
            throw std::runtime_error("option -" + lab + " has no value");
        }
        return str_as<T>(val);
    }

    template <class T>
    std::vector<T> get_all(const std::string &lab) const {
        auto &line = find(lab);
        return str_split<T>(line, ",; ");
    }

    void show_help(std::ostream &os = std::cout) const;
    int parse(int argc, char **argv);
};
