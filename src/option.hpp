#pragma once

#include <functional>
#include <map>
#include <vector>

using OptionCallback = std::function<int(int, char **)>;

class OptionParser {
    std::map<std::string, OptionCallback> options_;

   public:
    int parse(int argc, char **argv);

    template <class T>
    int read(int argc, char **argv, T &val);

    template <class T>
    int read(int argc, char **argv, std::vector<T> &vec) {
        char *arg = argv[0];
        int n = 0;
        vec.clear();
        while (arg[0] != '-') {
            T val;
            n += read(argc - n, argv + n, val);
            vec.push_back(val);
            if (argc - n == 0) break;
            arg = argv[n];
        }
        return n;
    }

    template <class T>
    OptionParser &add(const std::string &lbl, T &val) {
        options_.insert(std::make_pair(
            lbl, [&](int argc, char **argv) { return read(argc, argv, val); }));
        return *this;
    }

    template <class T>
    OptionParser &add(const std::string &lbl, std::function<void(T)> cb) {
        options_.insert(std::make_pair(lbl, [&](int argc, char **argv) {
            T val;
            int n = read(argc, argv, val);
            cb(val);
            return n;
        }));
        return *this;
    }

    OptionParser &add(const std::string &lbl, OptionCallback cb) {
        options_.insert(std::make_pair(lbl, cb));
        return *this;
    }
};
