#ifndef DRAW_HPP
#define DRAW_HPP

#include <stdexcept>

#include <cairo/cairo-svg.h>
#include <math.h>

#include "../utils/stringops.hpp"

class canvas {
   public:
    enum img_format { SVG, PNG };

    canvas(std::string name, img_format format, int width, int height);
    ~canvas();

    inline void push() { cairo_save(cr); }
    inline void pop() { cairo_restore(cr); }
    inline void flush() { cairo_surface_flush(surface); }
    inline void line_width(double w) { cairo_set_line_width(cr, w); }
    inline void rgba(double r, double g, double b, double a) {
        cairo_set_source_rgba(cr, r, g, b, a);
    }
    void draw_rectangle(double x, double y, double width, double height);
    void draw_arrow(double x1, double y1, double x2, double y2, double offset);
    void draw_point(double x, double y, double r);
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

#endif
