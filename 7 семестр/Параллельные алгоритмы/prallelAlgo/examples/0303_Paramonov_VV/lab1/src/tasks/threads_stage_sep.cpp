#include <vector>
#include <thread>

#include "tasks.h"
#include "../utils/matrix.h"

using namespace std;


void initializeMatrices(Matrix& first, Matrix& second) {
    first.randomInit(-20, 20);
    second.randomInit(-20, 20);
}

void multiplicateMatrices(Matrix& first, Matrix& second, Matrix& mulResult, int fRows, int sCols) {
    vector<int> computedRow; 
    for (int fRow=0; fRow < fRows; fRow++) {
        computedRow = first.multiplyRow(first, second, fRow);
        mulResult.setRow(fRow, computedRow);
    }
}

void outputMatrix(Matrix& mulResult, string& outFileName) {
    mulResult.writeMatrix(outFileName);
}

int threadsStageSep(int fRows, int fCols, int sRows, int sCols, string& outFileName, bool printToConsole) {
    Matrix first(fRows, fCols);
    Matrix second(sRows, sCols);
    Matrix mulResult(fRows, sCols);

    thread initialize(initializeMatrices, ref(first), ref(second));
    initialize.join();
    
    if (printToConsole) {
        cout << "First matrix:" << endl;
        first.printMatrix();
        cout << "Second matrix:" << endl;
        second.printMatrix();
    }

    thread multiplicate(multiplicateMatrices, ref(first), ref(second), ref(mulResult), fRows, sCols);
    multiplicate.join();

    if (printToConsole) {
        cout << "Multiplication result matrix:" << endl;
        mulResult.printMatrix();
    }

    thread output(outputMatrix, ref(mulResult), ref(outFileName));
    output.join();

    return 0;
}