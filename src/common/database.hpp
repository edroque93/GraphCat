#pragma once

#include <functional>
#include <sstream>
#include <string>
#include <vector>

#include "../utils/stringops.hpp"

class database {
    std::vector<std::string> header = {};
    std::vector<std::string> data = {};
    size_t nrows = 0;
    size_t ncols = 0;

    const std::string na = "-";

    const std::string &at(size_t i, size_t j) const;

   public:
    class record {
        const database &db;
        const size_t id;

       public:
        record(const database &d, size_t i) : db(d), id(i) {}

        template <class K>
        const std::string &operator[](K key) {
            return db.at(id, db.index(key));
        }

        template <class T, class K>
        T get(K key) const {
            return db.get<T>(id, key);
        }

        template <class T, class K>
        T get(K key, T def) const {
            return db.get<T>(id, key, def);
        }

        template <class K>
        bool is_set(K key) const {
            return db.is_set(id, key);
        }
    };

    inline size_t rows() const { return nrows; }
    inline size_t cols() const { return ncols; }

    record operator[](size_t i) const;
    std::vector<size_t> where(std::function<bool(const record &)> pred);

    static database read_csv(const std::string &filename);
    void save_csv(const std::string &filename, char delim = ' ');
    friend std::ostream &operator<<(std::ostream &, const database &);

    size_t index(size_t key) const;
    size_t index(const std::string &key) const;

    template <class T, class K>
    std::vector<T> values(K key) {
        std::vector<T> vec;
        vec.reserve(nrows);
        for (size_t i = 0; i < nrows; ++i) {
            vec.push_back(get<T>(i, key));
        }
        return std::move(vec);
    }

    template <class T, class K>
    std::vector<T> values(K key, T def) {
        std::vector<T> vec;
        vec.reserve(nrows);
        for (size_t i = 0; i < nrows; ++i) {
            vec.push_back(get<T>(i, key, def));
        }
        return std::move(vec);
    }

    template <class T, class K>
    T get(size_t i, K key) const {
        size_t j = index(key);
        if (j >= ncols) throw std::runtime_error("index out of bounds");
        const auto &val = at(i, j);
        if (val == na) throw std::runtime_error("value not available");
        return str_as<T>(val);
    }

    template <class T, class K>
    T get(size_t i, K key, T def) const {
        size_t j = index(key);
        if (j >= ncols) return def;
        const auto &val = at(i, j);
        if (val == na) return def;
        return str_as<T>(val);
    }

    template <class K>
    bool is_set(size_t i, K key) const {
        size_t j = index(key);
        if (j >= ncols) return false;
        const auto &val = at(i, j);
        return val != na;
    }
};
