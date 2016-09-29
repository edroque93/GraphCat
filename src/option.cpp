#include "option.hpp"

#include <exception>
#include <sstream>

int OptionParser::parse(int argc, char **argv) {
    int n = 0;
    while (n < argc) {
        char *arg = argv[n];

        // -opt [values]
        if (arg[0] != '-') break;

        std::string label = &arg[1];

        // -- signals end of options
        if (label == "-") return n + 1;

        auto it = options_.find(label);
        if (it == options_.end()) {
            throw std::logic_error("unknown option -" + label);
        }

        n += 1;

        // parse the option
        try {
            n += it->second(argc - n, argv + n);
        } catch (const std::exception &ex) {
            std::stringstream ss;
            ss << "option -" << label << ": " << ex.what();
            throw std::logic_error(ss.str());
        }
    }
    return n;
}

template <>
int OptionParser::read(int argc, char **argv, int &val) {
    if (argc <= 0) throw std::logic_error("no argument");
    std::string arg = argv[0];
    val = stoi(arg);
    return 1;
}

template <>
int OptionParser::read(int argc, char **argv, double &val) {
    if (argc <= 0) throw std::logic_error("no argument");
    std::string arg = argv[0];
    val = stod(arg);
    return 1;
}

template <>
int OptionParser::read(int argc, char **argv, std::string &val) {
    if (argc <= 0) throw std::logic_error("no argument");
    val = argv[0];
    return 1;
}

template <>
int OptionParser::read(int argc, char **argv, bool &val) {
    if (argc <= 0) throw std::logic_error("no argument");
    std::string arg = argv[0];
    if (arg == "yes") {
        val = true;
    } else if (arg == "no") {
        val = false;
    } else {
        throw std::logic_error("unexpected value: " + arg);
    }
    return 1;
}
