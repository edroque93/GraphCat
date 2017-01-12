#ifndef COMPUTE_HPP
#define COMPUTE_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

#include <gsl/gsl_eigen.h>
#include <gsl/gsl_vector.h>

#include "../common/topology.hpp"

class compute {
   private:
    // double buffering
    std::vector<vec2> points1;
    std::vector<vec2> points2;

    std::vector<vec2> &oldpos;
    std::vector<vec2> &newpos;

    const topology &the_topo;

    void normalize();
    vec2 repulsive(size_t i, size_t j);
    vec2 spring(size_t i, size_t j);

   public:
    compute(topology &topo)
        : oldpos(points1), newpos(points2), the_topo(topo) {}
    void generate_eigenvectors();
    void update();

    const std::vector<vec2> &get_points() { return oldpos; }
};

#endif
