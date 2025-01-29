#pragma once

#include <cstddef>
#include <matrix.h>

#define CL_TARGET_OPENCL_VERSION 220

constexpr size_t workgroupSize[] = { 16, 16 };
constexpr char kernelFile[] = "matrixOCL.cl";
constexpr char kernelFunc[] = "calcMatrixElem";

Matrix multiplyMatricesOcl(const Matrix& lm, const Matrix& rm);
