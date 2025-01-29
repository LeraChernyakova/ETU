#ifndef PROCESSES_CALCULATEPROCESS_H
#define PROCESSES_CALCULATEPROCESS_H

#include "Process.h"

class CalculateProcess : public Process
{
public:
    CalculateProcess();
    ~CalculateProcess();
    void run() override;

private:
    void calculateMatrix();
    
private:
    SharedMemory* m_sharedMemory;
};

#endif //PROCESSES_CALCULATEPROCESS_H
