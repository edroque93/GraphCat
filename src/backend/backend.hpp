#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <cairo/cairo-svg.h>

#include "../common/config.hpp"
#include "../common/database.hpp"
#include "../common/topology.hpp"
#include "../utils/stringops.hpp"
#include "canvas.hpp"

namespace backend {
void plot(const config &cfg, const topology &topo,
          const std::vector<vec2> &points, const database &attrib,
          std::string suffix = "");

const int default_margin = 32;
const int default_width = 512;
const int default_height = 512;
const canvas::img_format default_format = canvas::img_format::SVG;
};

#endif
