#include <vector>
#include <thread>

#include "tasks.h"
#include "../utils/matrix.h"

using namespace std;


void multiplicateRow(Matrix& first, Matrix& second, Matrix& mulResult, int threadNum, int rowsToThread) {
    vector<int> computedRow;
    for (int i=0; i < rowsToThread; i++) {
        computedRow = first.multiplyRow(first, second, rowsToThread*threadNum + i);
        mulResult.setRow(rowsToThread*threadNum + i, computedRow);
    }
}

int threadsMultiply(int fRows, int fCols, int sRows, int sCols, string& outFileName, bool printToConsole, 
                    int threadsNum) {
    Matrix first(fRows, fCols, -20, 20);
    Matrix second(sRows, sCols, -20, 20);
    Matrix mulResult(fRows, sCols);
    
    if (printToConsole) {
        cout << "First matrix:" << endl;
        first.printMatrix();
        cout << "Second matrix:" << endl;
        second.printMatrix();
    }
    // Деление задачи на потоки. Если кол-во строк первой матрицы не кратна числу потоков, то выходим с ошибкой.
    if (fRows % threadsNum > 0) {
        cout << "The number of rows of the first matrix is not a multiple of the number of threads!" << endl;
        exit(1);
    }
    vector<thread> mulThreads;
    if (threadsNum >= fRows)
        threadsNum = fRows;
    mulThreads = vector<thread>(threadsNum);
    int rowsToThread = fRows / threadsNum;


    
    for (int threadNum=0; threadNum < threadsNum; threadNum++) {
        mulThreads[threadNum] = thread(multiplicateRow, ref(first), ref(second), ref(mulResult), threadNum, rowsToThread);
    }

    for (int threadNum=0; threadNum < threadsNum; threadNum++) {
        mulThreads[threadNum].join();
    }

    if (printToConsole) {
        cout << "Multiplication result matrix:" << endl;
        mulResult.printMatrix();
    }

    mulResult.writeMatrix(outFileName);

    return 0;
}