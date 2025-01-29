#include <iostream>

#include "../utils/matrix.h"

using namespace std;


void threadsScalableMul(Matrix& first, Matrix& second, Matrix& mulResult, int threadInd, int threadsNum) {
    int mulResultElement, i, k;
    for (int ik = threadInd; ik < mulResult.getRows() * mulResult.getCols(); ik += threadsNum) {
        mulResultElement = 0;
        i = ik / mulResult.getCols();
        k = ik % mulResult.getCols();
        
        for (int j = 0; j < first.getCols(); j++) {
            mulResultElement += (first[i][j] * second[j][k]);
        }
        mulResult[i][k] = mulResultElement;
    }
}