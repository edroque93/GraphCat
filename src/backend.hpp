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

namespace backend {
void plot(const config &cfg, const topology &topo,
          const std::vector<vec2> &points, std::string suffix = "");

const int default_margin = 32;
const int default_width = 512;
const int default_height = 512;
const canvas::img_format default_format = canvas::img_format::SVG;
};

#endif // BACKEND_HPP
