#include "topology.hpp"

#include <fstream>
#include <stdexcept>

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "../utils/stringops.hpp"

using namespace std;

topology::~topology() {
    if (matrix != nullptr) gsl_matrix_free(matrix);
}

topology::topology(const topology &other) {
    matrix = gsl_matrix_alloc(other.size(), other.size());
    if (matrix == NULL) throw runtime_error("unable to allocate matrix");
    gsl_matrix_memcpy(matrix, other.matrix);
}

topology &topology::operator=(const topology &other) {
    if (this != &other) {
        if (size() != other.size()) {
            gsl_matrix_free(matrix);
            matrix = gsl_matrix_alloc(other.size(), other.size());
            if (matrix == NULL)
                throw runtime_error("unable to allocate matrix");
        }
        gsl_matrix_memcpy(matrix, other.matrix);
    }
    return *this;
}

topology::topology(topology &&other) {
    matrix = other.matrix;
    other.matrix = nullptr;
}

topology &topology::operator=(topology &&other) {
    if (this != &other) {
        gsl_matrix_free(matrix);
        matrix = other.matrix;
        other.matrix = nullptr;
    }
    return *this;
}

topology topology::read_csv(const string &filename) {
    topology top;
    string line;
    ifstream ifs(filename);

    const char *delim = ":;,\t ";

    if (!getline(ifs, line)) throw std::runtime_error("file is empty");
    vector<double> values = str_split<double>(line, delim);

    if (values.size() == 0) throw std::runtime_error("no values");

    size_t size = values.size();

    gsl_matrix *mat = gsl_matrix_alloc(size, size);
    if (mat == NULL) throw runtime_error("unable to allocate matrix");

    for (size_t j = 0; j < size; ++j) {
        gsl_matrix_set(mat, 0, j, values[j]);
    }

    for (size_t i = 1; i < size; ++i) {
        if (!getline(ifs, line)) {
            gsl_matrix_free(mat);
            throw std::runtime_error("unexpected end of file");
        }
        values = str_split<double>(line, delim);
        if (values.size() != size) {
            gsl_matrix_free(mat);
            throw std::runtime_error("wrong number of values");
        }

        for (size_t j = 0; j < size; ++j) {
            gsl_matrix_set(mat, i, j, values[j]);
        }
    }

    getline(ifs, line);
    if (!ifs.eof()) {
        gsl_matrix_free(mat);
        throw std::runtime_error("expected end of file");
    }

    top.matrix = mat;
    return top;
}

void topology::save_csv(const string &filename, char delim) {
    std::ofstream ofs(filename);
    for (size_t i = 0; i < size(); ++i) {
        for (size_t j = 0; j < size() - 1; ++j) {
            ofs << gsl_matrix_get(matrix, i, j) << delim;
        }
        ofs << gsl_matrix_get(matrix, i, size() - 1) << '\n';
    }
}

void topology::save_dat(const string &filename) {
    FILE *fp = fopen(filename.c_str(), "wb");
    if (fp == NULL) {
        throw std::runtime_error("unable to open file " + filename + ": " +
                                 strerror(errno));
    }
    if (gsl_matrix_fwrite(fp, matrix) != 0) {
        fclose(fp);
        throw std::runtime_error("unable to save matrix");
    }
    fclose(fp);
}

std::ostream &operator<<(ostream &os, const topology &top) {
    for (size_t i = 0; i < top.size(); ++i) {
        for (size_t j = 0; j < top.size(); ++j) {
            os << ' ' << gsl_matrix_get(top.matrix, i, j);
        }
        os << '\n';
    }
    return os;
}
