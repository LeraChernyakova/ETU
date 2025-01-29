#ifndef THREADS_TASKS_H
#define THREADS_TASKS_H

#include <thread>
#include <atomic>
#include <vector>

#include "common/matrix.h"


namespace threads
{

class Tasks
{
public:
    Tasks( size_t threadsCount = 1 );

    bool isValid() const;

    void readMatrices( common::Matrix& lhs, common::Matrix& rhs );
    void multiplyMatricesSerial( const common::Matrix& lhs, const common::Matrix& rhs, common::Matrix& result );
    void multiplyMatricesParallel( const common::Matrix& lhs, const common::Matrix& rhs
        , common::Matrix& result, size_t threadsCount );
    void writeResultMatrix( const common::Matrix& result );

private:
    void invalidate();
    void storeAtomicBool( std::atomic< bool >& atomic, bool value );
    void waitForAtomicBool( const std::atomic< bool >& atomic, bool value );

private:
    common::Matrix              lhs_;               ///< Левая умножаемая матрица.
    common::Matrix              rhs_;               ///< Правая умножаемая матрица.
    common::Matrix              result_;            ///< Результирующая матрица.

    std::vector< std::thread >  threads_;           ///< Рабочие потоки.

    std::atomic< bool >         isValid_;           ///< Валидность программы.
    std::atomic< bool >         calcAllowed_;       ///< Разрешение на чтение данных для второго потока.
    std::atomic< bool >         writeAllowed_;      ///< Разрешение на чтение данных для третьего потока.

}; // class Tasks

}; // namespace threads

#endif // THREADS_TASKS_H
