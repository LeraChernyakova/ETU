#include <unistd.h>
#include <functional>
#include <sys/wait.h>

#include "sharedMemory.h"
#include "../io/input.h"
#include "../io/output.h"
#include "../io/files.h"

// ================================================

void readMatrices() {
    std::vector<Matrix> matrices;
    readMatricesFromFile(INPUT_PROCESSES_FILE, &matrices);
    if(!isCorrectMatricesInput(matrices)) {
        exit(0);
    }
    std::vector<int> buffer = serializeManyMatrices(matrices);
    int* sharedPointer = (int*)getSharedMemoryPointer();
    writeToSharedPointer(sharedPointer, buffer);
    std::cout << "Process: read matrices.\n";
}

void calculate() {
    int* sharedPointer = (int*)getSharedMemoryPointer();
    std::vector<int> buffer = readFromSharedPointer(sharedPointer);
    std::vector<Matrix> matrices = deserializeManyMatrices(buffer);

    multiplyMatrices(&matrices);
    matrices.erase(matrices.begin(), matrices.begin()+2);

    std::vector<int> newBuffer = serializeManyMatrices(matrices);
    writeToSharedPointer(sharedPointer, newBuffer);
    std::cout << "Process: calculate.\n";
}

void writeMatrix() {
    int* sharedPointer = (int*)getSharedMemoryPointer();
    std::vector<int> buffer = readFromSharedPointer(sharedPointer);

    std::vector<Matrix> matrices = deserializeManyMatrices(buffer);
    writeMatrixToFile(OUTPUT_FILE, matrices[0]);
    std::cout << "Process: write matrix.\n";
}

// ================================================

void runProcess(const std::function<void()> &function) {
    pid_t pid = fork();
    switch(pid) {
        case 0:         // Потомок
            function();
            exit(0);
        case -1:        // Неудачная попытка создать процесс-потомок
            std::cout << "Error! Cannot fork process.\n";
            exit(-1);   // Выход из родительского процесса
        default:        // Родитель, pid>0
            wait(&pid); 
    }
}

int main() {
    runProcess(readMatrices);
    runProcess(calculate);
    runProcess(writeMatrix);

    std::cout << "\nSee answer in ./data/output.txt file.\n\n";
    return 0;
}
