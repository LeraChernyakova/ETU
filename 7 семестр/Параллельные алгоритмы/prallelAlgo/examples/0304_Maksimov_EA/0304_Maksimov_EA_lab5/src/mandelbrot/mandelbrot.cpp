#include "mandelbrot.h"

int computeIterations(const float x0, const float y0, int iterations) {
    int n = 0;

    for (float x = x0, y = y0; (x*x + y*y <= 2*2) && n < iterations; n++) { 
        float xtemp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtemp;
    }

    return n;
}


unsigned int computeColor(int itersTotal, float itersMax) { 
    float itersMin = itersMax - 50;
    int pos = 255 * std::max(0.f, itersTotal-itersMin) / (itersMax-itersMin);

    // Для CPU цвета:           (R,G,B)
    // Для GPU цвета другие:    (R,0,0)
    int red = (int)(pos);
    int green = (int)(pos);
    int blue = (int)(pos);

    return red | (green << 8) | (blue << 16);
}


void drawMandelbrot(
    float itersMax,
    int w, int h,
    unsigned int* result
) {
    for (int iy = 0; iy < h; iy++) {
        for (int ix = 0; ix < w; ix++) {
            float x = 5.0f * (float)((ix - w/2)) / w;
            float y = 5.0f * (float)((iy - h/2)) / h;
            int itersTotal = computeIterations(x, y, (int)itersMax); 
            result[iy * w + ix] = computeColor(itersTotal, itersMax); 
        }
    }

    return;
}
