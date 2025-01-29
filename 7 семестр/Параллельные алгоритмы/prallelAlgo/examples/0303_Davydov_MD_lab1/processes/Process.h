#ifndef PROCESSES_PROCESS_H
#define PROCESSES_PROCESS_H

#include "definitions.h"
#include "SharedMemory.h"

class Process
{
public:
    Process() {};
    ~Process(){};
    virtual void run() = 0;
};

#endif //PROCESSES_PROCESS_H
