#include "database.hpp"

#include <algorithm>
#include <exception>
#include <fstream>
#include <numeric>

using namespace std;

size_t database::index(const string &label) const {
    auto it = find(header.begin(), header.end(), label);
    if (it == header.end())
        throw runtime_error("label " + label + " not found");
    return it - header.begin();
}

const string &database::label(size_t j) const {
    if (j >= ncols) throw runtime_error("index out of bounds");
    return header[j];
}

database::record database::operator[](size_t i) const {
    if (i >= nrows) throw runtime_error("index out of bounds");
    return database::record(*this, i);
}

database database::read_csv(const string &filename) {
    database db;
    string line;
    ifstream ifs(filename);

    const char *delim = ":;,\t ";

    while (line.empty()) {
        if (!getline(ifs, line)) return db;
    }
    vector<string> values = str_split<string>(line, delim);

    if (values.size() == 0) return db;

    db.ncols = values.size();
    db.header = values;

    db.data.clear();

    while (getline(ifs, line)) {
        if (line.empty()) continue;
        values = str_split<string>(line, delim);
        if (values.size() != db.ncols)
            throw runtime_error("wrong number of values");
        db.data.insert(db.data.end(), values.begin(), values.end());
        db.nrows += 1;
    }

    return db;
}

void database::save_csv(const string &filename, char delim) {
    ofstream ofs(filename);

    for (size_t j = 0; j < ncols - 1; ++j) {
        ofs << header[j] << delim;
    }
    ofs << header[ncols-1] << '\n';

    for (size_t i = 0; i < nrows; ++i) {
        for (size_t j = 0; j < ncols - 1; ++j) {
            ofs << at(i,j) << delim;
        }
        ofs << at(i, ncols-1) << '\n';
    }
}

const string &database::at(size_t i, size_t j) const {
    if (i >= nrows || j >= ncols) throw runtime_error("index out of bounds");
    return data[i * ncols + j];
}

const std::string &database::at(size_t i, const std::string &label) const {
    return at(i, index(label));
}

ostream &operator<<(ostream &os, const database &db) {
    if (db.header.size() == 0) return os;

    vector<size_t> pad(db.cols(), 0);
    for (size_t j = 0; j < db.cols(); ++j) {
        size_t max_len = db.header[j].size();
        for (size_t i = 0; i < db.rows(); ++i) {
            max_len = max(max_len, db.at(i, j).size());
        }
        pad[j] = max_len;
    }

    for (size_t j = 0; j < db.cols(); ++j) {
        const auto &str = db.header[j];
        os << ' ' << str << string(pad[j] - str.size(), ' ');
    }

    size_t len = accumulate(pad.begin(), pad.end(), db.cols() - 1);
    os << "\n " << string(len, '=') << '\n';

    for (size_t i = 0; i < db.rows(); ++i) {
        for (size_t j = 0; j < db.cols(); ++j) {
            const auto &str = db.at(i, j);
            os << ' ' << str << string(pad[j] - str.size(), ' ');
        }
        os << '\n';
    }

    return os;
}
