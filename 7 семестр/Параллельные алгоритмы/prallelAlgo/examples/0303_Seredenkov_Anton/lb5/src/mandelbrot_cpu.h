#pragma once
#include <algorithm>
int compute_iterations(const float x0, const float y0, int iterations);
unsigned int color(int total_iters, float max_iters);
void mandelbrot(float max_iters, int w, int h, unsigned int* result);
