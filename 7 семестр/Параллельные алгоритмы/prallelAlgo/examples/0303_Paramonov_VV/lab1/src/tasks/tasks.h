#ifndef TASKS
#define TASKS

#include <string>

int processesStageSep(int fRows, int fCols, int sRows, int sCols, std::string& outFileName, bool printToConsole);
int threadsStageSep(int fRows, int fCols, int sRows, int sCols, std::string& outFileName, bool printToConsole);
int threadsMultiply(int fRows, int fCols, int sRows, int sCols, std::string& outFileName, bool printToConsole, int threadsNum);

#endif