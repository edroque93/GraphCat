#pragma once

#include <string>
#include <vector>
#include <functional>

#include "../utils/stringops.hpp"

class database {
    std::vector<std::string> header = {};
    std::vector<std::string> data = {};
    size_t nrows = 0;
    size_t ncols = 0;

   public:
    class record {
        const database &db;
        const size_t id;

       public:
        record(const database &d, size_t i) : db(d), id(i) {}

        template <class T>
        const std::string &operator[](T label) {
            return db.at(id, label);
        }

        template <class T, class U>
        T get(U j) const {
            return db.get<T>(id, j);
        }
    };

    inline size_t rows() const { return nrows; }
    inline size_t cols() const { return ncols; }

    const std::string &at(size_t i, size_t j) const;
    const std::string &at(size_t i, const std::string &label) const;

    size_t index(const std::string &label) const;
    const std::string &label(size_t j) const;

    template <class T, class U>
    std::vector<T> values(U j) {
        std::vector<T> vec;
        vec.reserve(nrows);
        for (size_t i = 0; i < nrows; ++i) {
            vec.push_back(get<T>(i, j));
        }
        return std::move(vec);
    }

    record operator[](size_t i) const;

    template <class T>
    T get(size_t i, size_t j) const {
        return str_as<T>(at(i, j));
    }

    template <class T>
    T get(size_t i, const std::string &label) const {
        return get<T>(i, index(label));
    }

    template <class T, class U>
    std::vector<size_t> where(U j, std::function<bool(T)> test) {
        std::vector<size_t> vec;
        for (size_t i = 0; i < nrows; ++i) {
            if (test(get<T>(i, j))) {
                vec.push_back(i);
            }
        }
        return std::move(vec);
    }

    static database read_csv(const std::string &filename);

    void save_csv(const std::string &filename, char delim = ' ');

    friend std::ostream &operator<<(std::ostream &, const database &);
};
