#pragma once

#include <cstddef>

#define CL_TARGET_OPENCL_VERSION 220

constexpr size_t workgroupSize[] = { 256, 1 };
constexpr size_t channels = 3;
constexpr float xScale[] = { -2.0f , 0.47f };
constexpr float yScale[] = { -1.12f, 1.12f };
constexpr char kernelFile[] = "mandelbrot.cl";
constexpr char kernelFunc[] = "mandelbrot";


void mandelbrotCpu(char *buffer, size_t width, size_t height, size_t maxIters);
void mandelbrotOpencl(char *buffer, size_t width, size_t height, size_t maxIters);
