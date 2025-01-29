#include "ReadProcess.h"
#include "CalculateProcess.h"
#include "WriteProcess.h"

int main() 
{
    pid_t readProcessID, calculateProcessID, writeProcessID;
    ReadProcess* readProcess;
    CalculateProcess* calculateProcess;
    WriteProcess* writeProcess;

    readProcessID = fork();
    
    switch (readProcessID) {
        case -1:
            creationError(std::string("readProcess"));
            return -1;
        case 0:
            calculateProcessID = fork();
            switch (calculateProcessID) {
                case -1:
                    creationError(std::string("calculateProcess"));
                    return -1;
                case 0:
                    writeProcessID = fork();
                    switch (writeProcessID) {
                        case -1:
                            creationError(std::string("writeProcess"));
                            return -1;
                        case 0:
                            writeProcess = new WriteProcess();
                            writeProcess->run();
                            delete writeProcess;
                            break;
                        default:
                            calculateProcess = new CalculateProcess();
                            calculateProcess->run();
                            wait(&writeProcessID);
                            delete calculateProcess;
                    }
                    break;
                default:
                    readProcess = new ReadProcess();
                    readProcess->run();
                    wait(&calculateProcessID);
                    delete readProcess;
            }
            break;
        default:
            wait(&readProcessID);
    }
    return 0;
}
