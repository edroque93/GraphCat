#include <backend.hpp>

void backend::doTheThing() {
    cairo_surface_t *surface = cairo_svg_surface_create("test.svg", 512, 512);
    cairo_t *cr = cairo_create(surface);

    cairo_set_line_width(cr, 40.96);
    cairo_move_to(cr, 76.8, 84.48);
    cairo_rel_line_to(cr, 51.2, -51.2);
    cairo_rel_line_to(cr, 51.2, 51.2);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER); /* default */
    cairo_stroke(cr);

    cairo_move_to(cr, 76.8, 161.28);
    cairo_rel_line_to(cr, 51.2, -51.2);
    cairo_rel_line_to(cr, 51.2, 51.2);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_BEVEL);
    cairo_stroke(cr);

    cairo_move_to(cr, 76.8, 238.08);
    cairo_rel_line_to(cr, 51.2, -51.2);
    cairo_rel_line_to(cr, 51.2, 51.2);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);
    cairo_stroke(cr);

    cairo_surface_flush(surface);
    cairo_surface_destroy(surface);
    cairo_destroy(cr);
}
