#include "backend.hpp"

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
    const double node_radius = 7.0;
    for (size_t i = 0; i < topo.size(); ++i) {
        int nodex = margin + (width - margin * 2) * vx[i];
        int nodey = margin + (height - margin * 2) * vy[i];
        cairo_arc(cr, nodex, nodey, node_radius, 0.0, M_PI * 2.0);
        cairo_set_source_rgba(cr, 0, 0, 1.0, 1.0);
        cairo_fill(cr);
        cairo_stroke(cr);
        for (size_t j = i; j < topo.size(); ++j) {
            if (topo.get(i, j)) {
                int nodex_end = margin + (width - margin * 2) * vx[j];
                int nodey_end = margin + (height - margin * 2) * vy[j];
                cairo_move_to(cr, nodex, nodey);
                cairo_line_to(cr, nodex_end, nodey_end);
                cairo_stroke(cr);

                draw_arrow(cr, nodex, nodey, nodex_end, nodey_end, node_radius);
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

void backend::draw_arrow(cairo_t *cr, double x1, double y1, double x2,
                         double y2, double offset) {
    const double arrow_angle = 30 * (M_PI / 180);
    const double arrow_side = 10.0;
    double arctan = atan2(y2 - y1, x2 - x1) + M_PI;
    x2 += cos(arctan) * offset;
    y2 += sin(arctan) * offset;
    double head_x1 = x2 + arrow_side * cos(arctan - arrow_angle);
    double head_y1 = y2 + arrow_side * sin(arctan - arrow_angle);
    double head_x2 = x2 + arrow_side * cos(arctan + arrow_angle);
    double head_y2 = y2 + arrow_side * sin(arctan + arrow_angle);
    cairo_move_to(cr, head_x1, head_y1);
    cairo_line_to(cr, x2, y2);
    cairo_line_to(cr, head_x2, head_y2);
    cairo_fill(cr);
}
