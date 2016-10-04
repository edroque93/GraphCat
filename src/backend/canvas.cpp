#include "canvas.hpp"

using namespace std;

canvas::canvas(std::string name, img_format format, int width, int height)
    : format(format), width(width), height(height) {
    switch (format) {
        case PNG:
            this->name = name + ".png";
            surface =
                cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
            break;
        case SVG:
        default:
            this->name = name + ".svg";
            surface =
                cairo_svg_surface_create(this->name.c_str(), width, height);
    }
    cr = cairo_create(surface);
}

canvas::~canvas() {
    if (format == PNG) {
        cairo_surface_write_to_png(surface, name.c_str());
    }
    cairo_surface_flush(surface);
    cairo_surface_destroy(surface);
    cairo_destroy(cr);
}

template <>
canvas::img_format str_as(const std::string &str) {
    if (str == "svg") return canvas::img_format::SVG;
    if (str == "png") return canvas::img_format::PNG;
    throw runtime_error("unknown image format " + str);
}

void canvas::watermark() {
    const char *text = "GraphCat";
    double x, y;
    cairo_text_extents_t extents;
    cairo_save(cr);
    cairo_set_source_rgba(cr, 1, 1, 1, 0.3);
    cairo_rotate(cr, -45 * (M_PI / 180));
    cairo_translate(cr, -width / 2, height / 4);
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, height * 120.0 / 512);
    cairo_text_extents(cr, text, &extents);
    x = width / 2 - (extents.width / 2 + extents.x_bearing);
    y = height / 2 - (extents.height / 2 + extents.y_bearing);
    cairo_move_to(cr, x, y);
    cairo_show_text(cr, text);
    cairo_restore(cr);
}

void canvas::draw_rectangle(double x, double y, double width, double height) {
    cairo_rectangle(cr, x, y, width, height);
    cairo_fill(cr);
}

void canvas::draw_arrow(double x1, double y1, double x2, double y2,
                        double offset) {
    draw_line(x1, y1, x2, y2);
    draw_arrow_head(x1, y1, x2, y2, offset);
}

void canvas::draw_point(double x, double y, double r) {
    cairo_arc(cr, x, y, r, 0.0, M_PI * 2.0);
    cairo_fill(cr);
    cairo_stroke(cr);
}

void canvas::draw_line(double x1, double y1, double x2, double y2) {
    cairo_move_to(cr, x1, y1);
    cairo_line_to(cr, x2, y2);
    cairo_stroke(cr);
}

void canvas::draw_arrow_head(double x1, double y1, double x2, double y2,
                             double offset) {
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
