#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <iostream>

#include <cairo/cairo-svg.h>
#include <math.h>

class backend {
   public:
    backend() {}
    backend(int width, int height);
    backend(int width, int height, int margin);
    // something something G(N,E)
    ~backend() {}
    void doTheThing();
   private:
    const int default_margin = 32;
    const int default_width = 512;
    const int default_height = 512;
    int width, height, margin;
};

#endif
