#pragma once

#include <thread>
#include <cmath>

#include "../model/matrix.h"

#define STRASSEN_MIN_SIZE 4
#define STRASSEN_RECURSION_LIMIT 3

void multiplyStrassen(std::vector<Matrix>* matrices, int N);
