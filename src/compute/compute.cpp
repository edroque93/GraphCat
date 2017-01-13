#include "compute.hpp"

#include <algorithm>
#include <limits>

using namespace std;

void compute::generate_eigenvectors() {
    gsl_matrix *topo = the_topo.copy_matrix();
    size_t dimension = topo->size1;
    points1.reserve(dimension);
    points2.reserve(dimension);

    // Weighted vector of topology in matrix diagonal

    gsl_matrix *diagonal = gsl_matrix_alloc(topo->size1, topo->size1);
    if (diagonal == NULL) throw runtime_error("unable to allocate matrix");

    for (size_t c = 0; c < dimension; ++c) {
        double sum = 0.;
        for (size_t r = 0; r < dimension; ++r) {
            sum += gsl_matrix_get(topo, r, c);
        }
        gsl_matrix_set(diagonal, c, c, sum);
    }

    // Get difference matrix

    gsl_matrix_sub(diagonal, topo);

    // Eigenvalues and eigenvectors

    gsl_vector *e_val = gsl_vector_alloc(dimension);
    gsl_matrix *e_vec = gsl_matrix_alloc(dimension, dimension);
    gsl_eigen_symmv_workspace *workspace = gsl_eigen_symmv_alloc(dimension);
    gsl_eigen_symmv(diagonal, e_val, e_vec, workspace);
    gsl_eigen_symmv_sort(e_val, e_vec, GSL_EIGEN_SORT_VAL_ASC);

    // Retrieve 2nd and 3rd eigenvector (ASC)

    gsl_vector_view vx_vv = gsl_matrix_column(e_vec, 1);
    gsl_vector_view vy_vv = gsl_matrix_column(e_vec, 2);

    // Normalize to 0..1 and add to vectors

    for (size_t i = 0; i < dimension; ++i) {
        vec2 point = {((1 + gsl_vector_get(&vx_vv.vector, i)) / 2),
                      ((1 + gsl_vector_get(&vy_vv.vector, i)) / 2)};

        points1.push_back(point);
        points2.push_back(point);
    }

    // Free structures

    gsl_matrix_free(topo);
    gsl_matrix_free(e_vec);
    gsl_vector_free(e_val);
    gsl_matrix_free(diagonal);
    gsl_eigen_symmv_free(workspace);
}

void compute::update() {
    auto size = oldpos.size();
    for (size_t i = 0; i < size; ++i) {
        vec2 disp = {0, 0};

        // global repulsive forces
        for (size_t j = 0; j < size; ++j) {
            if (i != j) {
                disp += repulsive(i, j);
            }
        }

        // local spring forces
        auto neighbours = the_topo.get_neighbours(i);
        for (auto j : neighbours) {
            disp += spring(i, j);
        }
        
        newpos[i] = oldpos[i] + disp;
    }

    normalize();

    std::swap(oldpos, newpos);
}

void compute::normalize() {
    vec2 max = {std::numeric_limits<double>::min(),
                std::numeric_limits<double>::min()};
    vec2 min = {std::numeric_limits<double>::max(),
                std::numeric_limits<double>::max()};
    for (auto &pt : oldpos) {
        min.x = std::min(pt.x, min.x);
        max.x = std::max(pt.x, max.x);
        min.y = std::min(pt.y, min.y);
        max.y = std::max(pt.y, max.y);
    }

    vec2 delta = max - min;
    for (auto &pt : oldpos) {
        pt.x = (max.x - pt.x) / delta.x;
        pt.y = (max.y - pt.y) / delta.y;
    }
}

vec2 compute::repulsive(size_t i, size_t j) {
    vec2 d = oldpos[j] - oldpos[i];
    return - d / d.size() * 0.01;
}

vec2 compute::spring(size_t i, size_t j) { return {0, 0}; }
