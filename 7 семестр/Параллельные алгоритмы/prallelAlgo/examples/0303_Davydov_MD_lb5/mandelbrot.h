#pragma once
#include <algorithm>
int compute_iterations(const float x0, const float y0, int iterations);
unsigned int compute_color(int total_iters, float max_iters);
void drawMandelbrot(float max_iters, int w, int h, unsigned int* result);
