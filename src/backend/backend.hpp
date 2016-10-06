#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

#include <cairo/cairo-svg.h>

#include "../common/config.hpp"
#include "../common/database.hpp"
#include "../common/topology.hpp"
#include "../utils/stringops.hpp"
#include "canvas.hpp"

class backend {
   public:
    backend(const topology &topo, const std::vector<double> &vx,
            const std::vector<double> &vy, const database &attrib)
        : topo(topo), vx(vx), vy(vy), attrib(attrib){};
    ~backend() { delete cairo; }
    void plot(const config &cfg);

   private:
    const int default_margin = 32;
    const int default_width = 512;
    const int default_height = 512;
    const canvas::img_format default_format = canvas::img_format::SVG;

    // TODO these are copies.. => make const& ?
    topology topo;
    std::vector<double> vx, vy;
    database attrib;
    canvas *cairo;

    void do_plot(int width, int height, int margin);
};

#endif
