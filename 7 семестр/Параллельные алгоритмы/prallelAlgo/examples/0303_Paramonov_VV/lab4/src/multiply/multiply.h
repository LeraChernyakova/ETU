#ifndef MULTIPLY
#define MULTIPLY

#include <vector>
#include <thread>

#include "../utils/matrix.h"


void threadsMulLab1(Matrix& first, Matrix& second, Matrix& mulResult, int threadInd, int threadsNum);
void threadsScalableMul(Matrix& first, Matrix& second, Matrix& mulResult, int threadInd, int threadsNum);
void threadsMulStrassen(Matrix first, Matrix second, Matrix& mulResult, int recursionDepth, int allowRecursionDepth);

#endif