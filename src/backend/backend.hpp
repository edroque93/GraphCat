#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <iostream>
#include <map>
#include <vector>
#include <stdexcept>

#include <cairo/cairo-svg.h>
#include <math.h>

#include "../common/database.hpp"
#include "../common/topology.hpp"
#include "../utils/stringops.hpp"

class backend {
   public:
    enum img_format { SVG, PNG };

    backend(const topology &topo, const std::vector<double> &vx,
            const std::vector<double> &vy, const database &attrib)
        : topo(topo), vx(vx), vy(vy), attrib(attrib){};
    ~backend() {}
    void plot(const database &format);
    void doTheThing();

   private:
    const int default_margin = 32;
    const int default_width = 512;
    const int default_height = 512;
    const img_format default_format = SVG;

    topology topo;
    std::vector<double> vx, vy;
    database attrib;

    void do_plot(int width, int height, int margin, const std::string &filename,
                 img_format ext);
};

#endif
