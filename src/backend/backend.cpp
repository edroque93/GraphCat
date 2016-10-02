#include "backend.hpp"

#include <exception>

using namespace std;

template <>
backend::img_format str_as(const std::string &str) {
    if (str == "svg") return backend::img_format::SVG;
    if (str == "png") return backend::img_format::PNG;
    throw runtime_error("unknown image format " + str);
}

void backend::plot(const database &format) {
    for (size_t i = 0; i < format.rows(); ++i) {
        int width, height, margin;
        string filename;
        img_format ext;
        auto rec = format[i];
        width = rec.get<int>("width", default_width);
        height = rec.get<int>("height", default_height);
        margin = rec.get<int>("margin", default_margin);
        filename = rec.get<string>("filename", "plot_" + to_string(i));
        ext = rec.get<img_format>("format", default_format);
        do_plot(width, height, margin, filename, ext);
    }
}

void backend::do_plot(int width, int height, int margin, const string &filename,
                      img_format ext) {
    cairo_surface_t *surface;
    switch (ext) {
        case PNG:
            surface =
                cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
            break;
        case SVG:
        default:
            string name = filename + ".svg";
            surface = cairo_svg_surface_create(name.c_str(), width, height);
    }
    cairo_t *cr = cairo_create(surface);
    cairo_set_line_width(cr, 1.0);

    for (size_t i = 0; i < topo.size(); ++i) {
        int nodex = margin + (width - margin * 2) * vx[i];
        int nodey = margin + (height - margin * 2) * vy[i];
        cairo_arc(cr, nodex, nodey, 7.0, 0.0, M_PI * 2.0);
        cairo_fill(cr);
        cairo_stroke(cr);
        for (size_t j = i; j < topo.size(); ++j) {
            if (topo.get(i, j)) {
                cairo_move_to(cr, nodex, nodey);
                cairo_line_to(cr, margin + (width - margin * 2) * vx[j],
                              margin + (height - margin * 2) * vy[j]);
                cairo_stroke(cr);
            }
        }
    }

    if (ext == PNG) {
        string name = filename + ".png";
        cairo_surface_write_to_png(surface, name.c_str());
    }

    cairo_surface_flush(surface);
    cairo_surface_destroy(surface);
    cairo_destroy(cr);
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
