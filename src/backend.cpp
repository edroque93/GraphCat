#include "backend.hpp"

using namespace std;

vec2 backend::translate(vec2 pos) {
    return {margin + (width - 2.0 * margin) * pos.x,
            margin + (height - 2.0 * margin) * pos.y};
}

void backend::plot(const std::vector<vec2> &points,
                   const std::string &filename) {
    canvas cairo(filename, fmt, width, height);
    cairo.rgba(1, 1, 1, 1);
    cairo.draw_rectangle(0, 0, width, height);
    for (size_t i = 0; i < topo.size(); ++i) {
        cairo.rgba(0, 0, 0, 1);
        vec2 pos = translate(points[i]);
        for (size_t j = i; j < topo.size(); ++j) {
            if (topo.connected(i, j)) {
                vec2 pos2 = translate(points[j]);
                cairo.draw_line(round(pos.x), round(pos.y), round(pos2.x),
                                round(pos2.y));
                continue;
            }
            if (topo.points_to(i, j)) {
                vec2 pos2 = translate(points[j]);
                cairo.draw_arrow(round(pos.x), round(pos.y), round(pos2.x),
                                 round(pos2.y), radius);
                continue;
            }
            if (topo.points_to(j, i)) {
                vec2 pos2 = translate(points[j]);
                cairo.draw_arrow(round(pos2.x), round(pos2.y), round(pos.x),
                                 round(pos.y), radius);
                continue;
            }
        }
    }
    for (size_t i = 0; i < topo.size(); ++i) {
        vec2 pos = translate(points[i]);
        cairo.draw_node(round(pos.x), round(pos.y), radius, to_string(i+1));
    }
}
