#include "threads_stage_sep.h"

using namespace std;


void initializeMatrices(int fRows, int fCols, int sRows, int sCols, 
                        baseThreadsQueue<Matrix*>& operationQueue, int numRepeats, int index, int numProducers) {
    for (int i = 0; i < numRepeats; i += numProducers) {
        Matrix *matrices = new Matrix[2];

        matrices[0] = Matrix(fRows, fCols, -20, 20);
        matrices[1] = Matrix(sRows, sCols, -20, 20);

        operationQueue.push(matrices);
    }
}

void multiplicateMatrices(baseThreadsQueue<Matrix*>& operationQueue, 
                            baseThreadsQueue<Matrix>& resultsQueue, int numRepeats, int index, int numConsumers) {
    for (int i = 0; i < numRepeats; i += numConsumers) {
        std::shared_ptr<Matrix *> matrices = operationQueue.pop();
        Matrix mulResult((*matrices)[0].getRows(), (*matrices)[1].getCols());
        
        vector<int> computedRow; 
        for (int fRow=0; fRow < (*matrices)[0].getRows(); fRow++) {
            computedRow = (*matrices)[0].multiplyRow((*matrices)[0], (*matrices)[1], fRow);
            mulResult.setRow(fRow, computedRow);
        }

        resultsQueue.push(mulResult);

        delete[] (*matrices);
    }
}

void outputMatrix(string& outFileName, baseThreadsQueue<Matrix>& resultsQueue, int numRepeats) {
    for (int i = 0; i < numRepeats; i++) {
        std::shared_ptr<Matrix> mulResult = resultsQueue.pop();
        (*mulResult).writeMatrix(outFileName); 
    }
}