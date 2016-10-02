#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <iostream>
#include <vector>

#include <cairo/cairo-svg.h>
#include <math.h>

#include "../common/topology.hpp"

/*
 Missing stuff:
 - G(N, E)
 - Output configuration
   - Surface type: SVG/PNG/...
   - W/H and margin

*/
class backend {
   public:
    backend(const topology &topo, const std::vector<double> &vx,
            const std::vector<double> &vy);
    ~backend() {}
    void doTheThing();

   private:
    const int default_margin = 32;
    const int default_width = 512;
    const int default_height = 512;
    int width, height, margin;
};

#endif
