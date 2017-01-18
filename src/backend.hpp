#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <cairo/cairo-svg.h>

#include "support/config.hpp"
#include "support/stringops.hpp"
#include "support/vector.hpp"

#include "canvas.hpp"
#include "topology.hpp"

class backend {
    const topology &topo;
    int margin = 32;
    int width = 512;
    int height = 512;
    canvas::img_format fmt = canvas::img_format::PNG;
    double radius = 7.0;

    vec2 translate(vec2 pos);

   public:
    backend(const topology &topo) : topo(topo) {}

    void set_margin(int m) { margin = m; }
    void set_width(int w) { width = w; }
    void set_height(int h) { height = h; }
    void set_format(canvas::img_format f) { fmt = f; }
    void set_radius(double r) { radius = r; }

    void plot(const std::vector<vec2> &points, const std::string &filename);
};

#endif  // BACKEND_HPP
