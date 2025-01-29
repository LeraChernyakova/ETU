#ifndef TASKS
#define TASKS

#include <string>
#include <vector>
#include <thread>

#include "../utils/matrix/matrix.h"
#include "../utils/threads_queue/base_threads_queue.h"

void initializeMatrices(int fRows, int fCols, int sRows, int sCols, baseThreadsQueue<Matrix*>& operationQueue, 
                        int numRepeats, int index, int numProducers);
void multiplicateMatrices(baseThreadsQueue<Matrix*>& operationQueue, baseThreadsQueue<Matrix>& resultsQueue, 
                        int numRepeats, int index, int numConsumers);
void outputMatrix(std::string& outFileName, baseThreadsQueue<Matrix>& resultsQueue, int numRepeats);

#endif