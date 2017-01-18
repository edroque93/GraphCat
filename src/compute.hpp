#ifndef COMPUTE_HPP
#define COMPUTE_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

#include <gsl/gsl_eigen.h>
#include <gsl/gsl_vector.h>

#include "support/vector.hpp"
#include "topology.hpp"

class compute {
   private:
    // double buffering
    std::vector<vec2> points1;
    std::vector<vec2> points2;

    std::vector<vec2> &oldpos;
    std::vector<vec2> &newpos;

    const topology topo;

    double repulsive(double x, double w);
    double spring(double x, double d, double w);

    double spring_factor = 0.1;
    double big_c = 0.05;
    double tolerance = 0.01;

    double nonzero(double d) {
        return (d < 0) ? std::min(-1e-10, d) : std::max(1e-10, d);
    }

    void estimate_params();

   public:
    compute(topology topo);

    void generate_eigenvectors();
    bool update(); // returns true if converged

    const std::vector<vec2> &get_points() { return oldpos; }
};

#endif  // COMPUTE_HPP
