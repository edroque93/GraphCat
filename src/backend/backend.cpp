#include <math.h>
#include <backend.hpp>
#include <iostream>

void backend::doTheThing() {
    const int width = 512;
    const int height = 512;
    const int margin = 32;
    const int nodes = 4;
    const double x[] = {0., 0.33, 0.66, 1.};
    const double y[] = {0., 0.33, 0.33, 0.};
    const bool edges[nodes][nodes] = {
        {0, 1, 1, 1}, {0, 0, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}};

    cairo_surface_t *surface =
        cairo_svg_surface_create("test.svg", width, height);
    cairo_t *cr = cairo_create(surface);
    cairo_set_line_width(cr, 1.0);

    for (int i = 0; i < nodes; i++) {
        int nodex = margin + (width - margin * 2) * x[i];
        int nodey = margin + (height - margin * 2) * y[i];
        cairo_arc(cr, nodex, nodey, 10.0, 0.0, M_PI * 2.0);
        cairo_fill(cr);
        cairo_stroke(cr);
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
