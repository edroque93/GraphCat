#include "config.hpp"

using namespace std;

const string &config::section::operator[](const string &) const {
    // TODO Fill in code for section::operator[]
    return values.begin()->second;
}

bool config::section::is_set(const string &key) const {
    // TODO Fill in code for section::is_set
    return false;
}

config config::read_ini(const string &filename) {
    // TODO Fill in code for config::read_ini
    config cfg;
    return move(cfg);
}

void config::save_ini(const string &filename) {
    // TODO Fill in code for config::save_ini
}

bool config::has_section(const string &) const {
    // TODO Fill in code for config::has_section
    return false;
}

config::section config::operator[](const string &name) const {
    // TODO Fill in code for config::operator[]
    config::section sec(name, values.begin()->second);
    return move(sec);
}
