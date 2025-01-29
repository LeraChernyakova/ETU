#ifndef PROCESSES_SHAREDMEMORY_H
#define PROCESSES_SHAREDMEMORY_H

#include "definitions.h"

struct MemoryBlock {
    Matrix<double> matrixA;
    Matrix<double> matrixB;
    Matrix<double> matrixC;
    status readingProcessStatus = START;
    status calculationProcessStatus = START;
    status writingProcessStatus = START;
    bool isCrash = false; //if true, it is gg
};

class SharedMemory 
{
public:
    SharedMemory(process);
    ~SharedMemory();
    
    bool checkMemory() const;
    
    void setProcessStatus(process, status);
    status getProcessStatus(process) const;
    
    void crash();
    bool isCrash() const;
    
    void setValue(double, matrix, int, int);
    double getValue(matrix, int, int) const;
    
    int getMatrixHeight(matrix) const;
    int getMatrixWidth(matrix) const;
    
private:
    process m_currentProcess;
    int m_memoryBlockID;
    MemoryBlock* m_memoryBlock;
};

#endif //PROCESSES_SHAREDMEMORY_H
