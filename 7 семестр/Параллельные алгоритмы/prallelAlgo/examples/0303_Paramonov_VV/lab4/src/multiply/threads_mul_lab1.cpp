#include "../utils/matrix.h"

using namespace std;


void threadsMulLab1(Matrix& first, Matrix& second, Matrix& mulResult, int threadInd, int threadsNum) {
    vector<int> computedRow;
    for (int i = threadInd; i < mulResult.getRows(); i += threadsNum) {
        computedRow = first.multiplyRow(first, second, i);
        mulResult[i] = computedRow;
    }
}