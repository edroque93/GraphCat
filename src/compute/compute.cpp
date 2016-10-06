#include "compute.hpp"

using namespace std;

void compute::generate_eigenvectors(const topology &original,
                                    std::vector<double> &vx,
                                    std::vector<double> &vy) {
    gsl_matrix *topo = original.copy_matrix();
    size_t dimension = topo->size1;

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
        vx.push_back((1 + gsl_vector_get(&vx_vv.vector, i)) / 2);
        vy.push_back((1 + gsl_vector_get(&vy_vv.vector, i)) / 2);
    }

    // Free structures

    gsl_matrix_free(topo);
    gsl_matrix_free(e_vec);
    gsl_vector_free(e_val);
    gsl_matrix_free(diagonal);
    gsl_eigen_symmv_free(workspace);
}
