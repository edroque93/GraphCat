#include "backend.hpp"

using namespace std;

void backend::plot(const config &cfg, const topology &topo,
                   const std::vector<double> &vx, const std::vector<double> &vy,
                   const database &attrib) {
    auto out = cfg["output"];
    int width = out.get<int>("width", backend::default_width);
    int height = out.get<int>("height", backend::default_height);
    int margin = out.get<int>("margin", backend::default_margin);
    canvas cairo(out.get<string>("filename", "plot"),
                 out.get<canvas::img_format>("type", backend::default_format),
                 width, height);
    cairo.rgba(0.86, 0.77, 0.87, 1.0);
    cairo.draw_rectangle(0, 0, width, height);
    cairo.watermark();
    const double node_radius = 7.0;
    for (size_t i = 0; i < topo.size(); ++i) {
        cairo.rgba(0, 0, 0, 1);
        int nodex = margin + (width - margin * 2) * vx[i];
        int nodey = margin + (height - margin * 2) * vy[i];
        cairo.draw_point(nodex, nodey, node_radius);
        for (size_t j = i; j < topo.size(); ++j) {
            if (topo.get(i, j) && topo.get(j, i)) {
                int nodex_end = margin + (width - margin * 2) * vx[j];
                int nodey_end = margin + (height - margin * 2) * vy[j];
                cairo.draw_line(nodex, nodey, nodex_end, nodey_end);
                continue;
            }
            if (topo.get(i, j) && !topo.get(j, i)) {
                int nodex_end = margin + (width - margin * 2) * vx[j];
                int nodey_end = margin + (height - margin * 2) * vy[j];
                cairo.draw_arrow(nodex, nodey, nodex_end, nodey_end,
                                 node_radius);
                continue;
            }
            if (!topo.get(i, j) && topo.get(j, i)) {
                int nodex_end = margin + (width - margin * 2) * vx[j];
                int nodey_end = margin + (height - margin * 2) * vy[j];
                cairo.draw_arrow(nodex_end, nodey_end, nodex, nodey,
                                 node_radius);
                continue;
            }
        }
    }
}
