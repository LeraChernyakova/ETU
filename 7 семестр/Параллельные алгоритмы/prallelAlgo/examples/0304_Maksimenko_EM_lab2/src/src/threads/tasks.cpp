#include "threads/tasks.h"

#include "common/defs.h"
#include "threads/matrix_algorithms.h"

#if defined( DEBUG )
#include <iostream>
#endif // defined( DEBUG )


threads::TaskGen threads::Tasks::generateMatrices()
{
    constexpr size_t rows1 = 4;
    constexpr size_t columns1Rows2 = 8;
    constexpr size_t columns2 = 7;
    
    threads::TaskGen task{ { 0, 0 }, { 0, 0 } };
    task.first = threads::generateMatrix( rows1, columns1Rows2 );
#ifdef DEBUG
    std::cout << "Generated matrix lhs\n";
    common::Matrix::write( task.first, std::cout );
#endif // DEBUG
    task.second = threads::generateMatrix( columns1Rows2, columns2 );
#ifdef DEBUG
    std::cout << "Generated matrix rhs\n";
    common::Matrix::write( task.second, std::cout );
#endif // DEBUG
    return task;
} // generateMatrices


void threads::Tasks::multiplyMatricesSerial( const TaskGen& task, ThreadFactory< TaskOut >& outQueue )
{
    TaskOut taskOut = threads::multiplyMatricesSerial( task.first, task.second );
    outQueue.addTask( std::move( taskOut ) );
#ifdef DEBUG
    std::cout << "Calculation ended\n";
#endif // DEBUG
} // multiplyMatricesSerial


void threads::Tasks::multiplyMatricesParallel( const TaskGen& task
    , ThreadFactory< TaskOut >& outQueue, size_t threadsCount )
{
    TaskOut taskOut = threads::multiplyMatricesParallel( task.first, task.second, threadsCount );
    outQueue.addTask( std::move( taskOut ) );
#ifdef DEBUG
    std::cout << "Calculation ended\n";
#endif // DEBUG
} // multiplyMatricesParallel


void threads::Tasks::writeResultMatrix( const threads::TaskOut& task )
{
    /// Вывод результата в файл
#ifdef DEBUG
    std::cout << "Result matrix\n";
    common::Matrix::write( task, std::cout );
#else
    (void) task;
#endif // DEBUG
} // writeResultMatrix
