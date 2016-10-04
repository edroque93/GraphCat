#ifndef COMPUTE_HPP
#define COMPUTE_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

#include <gsl/gsl_eigen.h>

#include "../common/topology.hpp"

class compute {
   public:
    compute(const topology &topo) : topo(topo.copy_matrix()){};
    void generate_eigenvectors(std::vector<double> &vx,
                               std::vector<double> &vy);
    ~compute(){
        // TODO frees
    };

   private:
    gsl_matrix *topo;
};

#endif
