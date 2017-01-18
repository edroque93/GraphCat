#ifndef TOPOLOGY_HPP
#define TOPOLOGY_HPP

#include <algorithm>
#include <array>
#include <ostream>
#include <string>
#include <vector>

#include <gsl/gsl_matrix.h>

#include "generator/node.hpp"

class topology {
    gsl_matrix *matrix = nullptr;
    topology(){};

   public:
    ~topology();

    topology(const topology &);
    topology &operator=(const topology &);

    topology(topology &&);
    topology &operator=(topology &&);

    size_t size() const { return matrix->size1; }
    double get(size_t i, size_t j) const {
        return gsl_matrix_get(matrix, i, j);
    }
    bool is_neighbour(size_t i, size_t j) const { return get(i, j) > 0; }
    std::vector<size_t> get_neighbours(size_t i) const;

    void fix_identity();
    gsl_matrix *copy_matrix() const;

    static topology generate_topology(const std::vector<node *> &graph);
    static topology read_csv(const std::string &filename);
    static topology read_dat(const std::string &filename);

    void save_csv(const std::string &filename, char delim = ' ');
    void save_dat(const std::string &filename);

    friend std::ostream &operator<<(std::ostream &os, const topology &top);

    std::string debug() const;
};

#endif // TOPOLOGY_HPP
