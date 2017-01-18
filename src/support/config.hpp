#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <exception>
#include <map>
#include <string>

#include "stringops.hpp"

class config;

class config {
   public:
    class section {
       public:
        const std::string name;
        std::map<std::string, std::string> values;

        section(const std::string n) : name(n) {}

        const std::string &retrieve(const std::string &) const;
        const std::string &operator[](const std::string &key) const {
            return retrieve(key);
        }
        std::string &operator[](const std::string &key) {
            return const_cast<std::string &>(retrieve(key));
        }

        bool is_set(const std::string &key) const;

        template <class T>
        T get(const std::string &key) const {
            if (!is_set(key)) throw std::runtime_error(key + " not set");
            return str_as<T>(this->retrieve(key));
        }

        template <class T>
        T get(const std::string &key, T def) const {
            return is_set(key) ? str_as<T>(this->retrieve(key)) : def;
        }
    };

   private:
    std::vector<section> sections;

   public:
    static config read_ini(const std::string &filename);
    void save_ini(const std::string &filename);

    bool has_section(const std::string &) const;

    const section &retrieve(const std::string &) const;
    const section &operator[](const std::string &key) const {
        return retrieve(key);
    }
    section &operator[](const std::string &key) {
        return const_cast<section &>(retrieve(key));
    }

    friend std::ostream &operator<<(std::ostream &os, const config &cfg);
};

#endif  // CONFIG_HPP
