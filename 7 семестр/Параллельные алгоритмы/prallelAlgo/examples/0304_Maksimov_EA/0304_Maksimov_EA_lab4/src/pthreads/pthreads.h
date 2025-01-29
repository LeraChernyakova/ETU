#pragma once

#include <thread>
#include <cmath>

#include "../model/matrix.h"

void multiplyMatricesMultithreadRoutine(std::vector<Matrix>* matricesPointer, int indexFirst, int indexLast);
void multiplyMatrciesMultithread(std::vector<Matrix>* matrices, int N);
