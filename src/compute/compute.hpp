#ifndef COMPUTE_HPP
#define COMPUTE_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

#include <gsl/gsl_eigen.h>
#include <gsl/gsl_vector.h>

#include "../common/topology.hpp"

namespace compute {
void generate_eigenvectors(const topology &original, std::vector<double> &vx,
                           std::vector<double> &vy);
};

#endif
