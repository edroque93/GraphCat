#include "backend.hpp"

backend::backend(const topology &topo, const std::vector<double> &vx,
                 const std::vector<double> &vy) {
    
}

void backend::doTheThing() {
    const int width = 512;
    const int height = 512;
    const int margin = 128;
    const int nodes = 13;
    const double x[] = {0.0, 0.05, 0.15, 0.25, 0.25, 0.40, 0.5,
                        0.6, 0.75, 0.75, 0.85, 0.95, 1.0};
    const double y[] = {0.3,  0.1, 0.0,  0.75, 0.1, 0.25, 1.0,
                        0.25, 0.1, 0.75, 0.0,  0.1, 0.3};
    const bool edges[nodes][nodes] = {
        {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1},
        {0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    };

    cairo_surface_t *surface =
        cairo_svg_surface_create("test.svg", width, height);
    cairo_t *cr = cairo_create(surface);
    cairo_set_line_width(cr, 1.0);

    for (int i = 0; i < nodes; i++) {
        int nodex = margin + (width - margin * 2) * x[i];
        int nodey = margin + (height - margin * 2) * y[i];
        // cairo_arc(cr, nodex, nodey, 7.0, 0.0, M_PI * 2.0);
        // cairo_fill(cr);
        // cairo_stroke(cr);
        for (int j = i; j < nodes; j++) {
            if (edges[i][j]) {
                cairo_move_to(cr, nodex, nodey);
                cairo_line_to(cr, margin + (width - margin * 2) * x[j],
                              margin + (height - margin * 2) * y[j]);
                std::cout << "From (" << nodex << ", " << nodey << ") to ("
                          << margin + (width - margin * 2) * x[j] << ", "
                          << margin + (height - margin * 2) * y[j] << ")"
                          << std::endl;
                cairo_stroke(cr);
            }
        }
    }

    cairo_surface_flush(surface);
    cairo_surface_destroy(surface);
    cairo_destroy(cr);
}
