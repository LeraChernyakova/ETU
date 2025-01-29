#ifndef THREADS_TASKS_H
#define THREADS_TASKS_H

#include <thread>
#include <atomic>
#include <vector>

#include "common/matrix.h"
#include "threads/thread_factory.hpp"

namespace threads
{

using TaskGen = std::pair< common::Matrix, common::Matrix >;
using TaskOut = common::Matrix;

class Tasks
{
public:
    static TaskGen generateMatrices();
    static void multiplyMatricesSerial( const TaskGen& task, ThreadFactory< TaskOut >& outQueue );
    static void multiplyMatricesParallel( const TaskGen& task, ThreadFactory< TaskOut >& outQueue, size_t threadsCount );

    static void writeResultMatrix( const TaskOut& task );
}; // class Tasks

} // namespace threads

#endif // THREADS_TASKS_H
