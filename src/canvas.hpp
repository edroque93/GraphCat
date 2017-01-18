#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <stdexcept>

#include <cairo/cairo-svg.h>
#include <math.h>

#include "support/stringops.hpp"

class canvas {
   public:
    enum img_format { SVG, PNG };

    canvas(std::string name, img_format format, int width, int height);
    ~canvas();

    void save() { cairo_save(cr); }
    void restore() { cairo_restore(cr); }
    void flush() { cairo_surface_flush(surface); }
    void line_width(double w) { cairo_set_line_width(cr, w); }
    void rgba(double r, double g, double b, double a) {
        cairo_set_source_rgba(cr, r, g, b, a);
    }

    void draw_node(double x, double y, double r, const std::string &txt="");
    void draw_rectangle(double x, double y, double width, double height);
    void draw_arrow(double x1, double y1, double x2, double y2, double offset);
    void draw_line(double x1, double y1, double x2, double y2);
    void draw_arrow_head(double x1, double y1, double x2, double y2,
                         double offset);
    void watermark();

   private:
    std::string name;
    img_format format;
    cairo_surface_t *surface;
    cairo_t *cr;
    int width, height;
};

#endif // CANVAS_HPP
