#ifndef MANDELBROT_CL_H
#define MANDELBROT_CL_H

#include "mandelbrot.h"

class MandelbrotCl: public Mandelbrot
{
public:
    MandelbrotCl( size_t w, size_t h, size_t iterations = 100 );

    void Generate() override;

};

#endif // MANDELBROT_CL_H
