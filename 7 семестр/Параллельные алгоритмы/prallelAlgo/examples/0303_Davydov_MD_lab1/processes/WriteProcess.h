#ifndef PROCESSES_WRITEPROCESS_H
#define PROCESSES_WRITEPROCESS_H

#include "Process.h"

class WriteProcess : public Process
{
public:
    WriteProcess();
    ~WriteProcess();
    void run() override;

private:
    void writeMatrix();

private:
    SharedMemory* m_sharedMemory;
};

#endif //PROCESSES_WRITEPROCESS_H
