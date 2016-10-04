#include "compute.hpp"

#include <gsl/gsl_vector.h>

using namespace std;

void compute::generate_eigenvectors(std::vector<double> &vx,
                                    std::vector<double> &vy) {
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
    gsl_eigen_symmv_free(workspace);

    // Retrieve 2nd and 3rd eigenvector

    gsl_vector_view vx_vv = gsl_matrix_column(e_vec, 1);
    gsl_vector_view vy_vv = gsl_matrix_column(e_vec, 2);

    // Normalize to 0..1

    for (size_t i = 0; i < dimension; ++i) {
        vx_vv.vector.data[i] = (1 + vx_vv.vector.data[i]) / 2;
        vy_vv.vector.data[i] = (1 + vy_vv.vector.data[i]) / 2;
    }

    vx.insert(vx.end(), &vx_vv.vector.data[0], &vx_vv.vector.data[dimension]);
    vy.insert(vy.end(), &vy_vv.vector.data[0], &vy_vv.vector.data[dimension]);

    // TODO Free allocs here xdddd
}

/*
Online octave check:

A=[0,1,1,0;1,0,0,1;1,0,0,1;0,1,1,0];
D=[2,0,0,0;0,2,0,0;0,0,2,0;0,0,0,2];
L=D-A;
disp(D);
disp(L);
[v, e] = eigs(L);
disp(v)

--

   2   0   0   0
   0   2   0   0
   0   0   2   0
   0   0   0   2

   2  -1  -1   0
  -1   2   0  -1
  -1   0   2  -1
   0  -1  -1   2

   0.50000   0.67458  -0.21200   0.50000
  -0.50000   0.21200   0.67458   0.50000
  -0.50000  -0.21200  -0.67458   0.50000
   0.50000  -0.67458   0.21200   0.50000

*/
