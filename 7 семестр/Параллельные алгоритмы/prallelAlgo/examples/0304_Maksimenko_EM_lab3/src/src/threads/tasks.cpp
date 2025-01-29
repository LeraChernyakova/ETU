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


void threads::Tasks::multiplyMatricesSerial( const TaskGen& task )
{
    TaskOut taskOut = threads::multiplyMatricesSerial( task.first, task.second );
#ifdef DEBUG
    std::cout << "Calculation ended\n";
    common::Matrix::write( task, std::cout );
#endif // DEBUG
} // multiplyMatricesSerial
