#pragma once
#include <algorithm>

unsigned int to_color_gray(int total_iters, float max_iters);

int compute_iterations(const float x0, const float y0, int iterations);

void mandelbrot(float px, float py, float mag, int max_iters, int w, int h, unsigned int* result, int result_step);