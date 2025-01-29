#ifndef PROCESSES_READPROCESS_H
#define PROCESSES_READPROCESS_H

#include "Process.h"

class ReadProcess: public Process 
{
public:
    ReadProcess();
    ~ReadProcess();
    void run() override;

private:
    void readMatrix(std::string, matrix);
    
private:    
    SharedMemory* m_sharedMemory;
    std::string m_AMatrixFileName;
    std::string m_BMatrixFileName;
};

#endif //PROCESSES_READPROCESS_H
