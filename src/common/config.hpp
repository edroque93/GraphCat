#pragma once

#include <exception>
#include <map>
#include <string>

#include "../utils/stringops.hpp"

// TODO does config need to be 'immutable'?

class config {
    std::map<std::string, std::map<std::string, std::string> > values;

   public:
    class section {
        const std::string &name;
        const std::map<std::string, std::string> &values;

       public:
        section(const std::string &n,
                const std::map<std::string, std::string> &v)
            : name(n), values(v) {}

        const std::string &operator[](const std::string &) const;
        bool is_set(const std::string &key) const;

        // TODO this can be optimized..
        template <class T>
        T get(const std::string &key) const {
            if (!is_set(key)) throw std::runtime_error(key + " not set");
            return str_as<T>((*this)[key]);
        }

        template <class T>
        T get(const std::string &key, T def) const {
            return is_set(key) ? str_as<T>((*this)[key]) : def;
        }
    };

    static config read_ini(const std::string &filename);
    void save_ini(const std::string &filename);

    bool has_section(const std::string &) const;
    section operator[](const std::string &) const;

    friend std::ostream &operator<<(std::ostream &os, const config &cfg);
};
