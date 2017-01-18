#ifndef COMPUTE_HPP
#define COMPUTE_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

#include <gsl/gsl_eigen.h>
#include <gsl/gsl_vector.h>

#include "topology.hpp"
#include "support/vector.hpp"

class compute {
   private:
    // double buffering
    std::vector<vec2> points1;
    std::vector<vec2> points2;

    std::vector<vec2> &oldpos;
    std::vector<vec2> &newpos;

    const topology &topo;

    vec2 repulsive(size_t i, size_t j);
    vec2 spring(size_t i, size_t j);

    double repulsive(double x, double w);
    double spring(double x, double d, double w);

    double spring_factor = 0.1;
    double big_c = 0.05;

    double nonzero(double d) {
        if (d < 0) {
            return std::min(-1e-10, d);
        } else {
            return std::max(1e-10, d);
        }
    }

   public:
    compute(topology &topo)
        : oldpos(points1), newpos(points2), topo(topo) {}
    void generate_eigenvectors();
    void update();
    void normalize();

    const std::vector<vec2> &get_points() { return oldpos; }
};

#endif // COMPUTE_HPP