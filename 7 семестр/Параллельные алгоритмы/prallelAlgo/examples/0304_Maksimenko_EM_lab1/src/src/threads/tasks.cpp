#include "threads/tasks.h"

#include "common/defs.h"
#include "threads/matrix_algorithms.h"

#include <iostream>
#include <fstream>


threads::Tasks::Tasks( size_t threadsCount )
    : lhs_{ 0, 0 }
    , rhs_{ 0, 0 }
    , result_{ 0, 0 }
    , isValid_{ true }
    , calcAllowed_{ false }
    , writeAllowed_{ false }
{
    threads_.emplace_back( &threads::Tasks::readMatrices, this
        , std::ref( lhs_ ), std::ref( rhs_ ) );
    if ( threadsCount > 1 )
    {
        threads_.emplace_back( &threads::Tasks::multiplyMatricesParallel, this
            , std::cref( lhs_ ), std::cref( rhs_ ), std::ref( result_ ), threadsCount );
    }
    else
    {
        threads_.emplace_back( &threads::Tasks::multiplyMatricesSerial
            , this, std::cref( lhs_ ), std::cref( rhs_ ), std::ref( result_ ) );
    }
    threads_.emplace_back( &threads::Tasks::writeResultMatrix, this, std::cref( result_ ) );

    for ( auto& thread: threads_ )
    {
        thread.join();
    }
} // Tasks


bool threads::Tasks::isValid() const
{
    return isValid_.load( std::memory_order_seq_cst );
} // isValid


void threads::Tasks::readMatrices( common::Matrix& lhs, common::Matrix& rhs )
{
    std::ifstream inStream( common::defs::inFile, std::ios_base::in );
    if ( !inStream.is_open() )
    {
        std::cerr << "Cannot open file " << common::defs::inFile << '\n';
        invalidate();
        return;
    }

    if ( !common::Matrix::read( lhs, inStream ) )
    {
        std::cerr << "Bad data for lhs matrix\n";
        invalidate();
        return;
    }
#ifdef DEBUG
    std::cout << "Read matrix lhs\n";
    common::Matrix::write( lhs, std::cout );
#endif // DEBUG
    if ( !common::Matrix::read( rhs, inStream ) )
    {
        std::cerr << "Bad data for rhs matrix\n";
        invalidate();
        return;
    }
#ifdef DEBUG
    std::cout << "Read matrix rhs\n";
    common::Matrix::write( rhs, std::cout );
#endif // DEBUG

    storeAtomicBool( calcAllowed_, true );
} // readMatrices


void threads::Tasks::multiplyMatricesSerial( const common::Matrix& lhs, const common::Matrix& rhs, common::Matrix& result )
{
    waitForAtomicBool( calcAllowed_, true );
    if ( !isValid_.load( std::memory_order_seq_cst ) )
    {
        std::cerr << "multiplyMatricesSerial invalidated\n";
        return;
    }

    result = threads::multiplyMatricesSerial( lhs, rhs );
#ifdef DEBUG
    std::cout << "Result matrix\n";
    common::Matrix::write( result, std::cout );
#endif // DEBUG

    storeAtomicBool( writeAllowed_, true );
} // multiplyMatricesSerial


void threads::Tasks::multiplyMatricesParallel( const common::Matrix& lhs, const common::Matrix& rhs
        , common::Matrix& result, size_t threadsCount )
{
    waitForAtomicBool( calcAllowed_, true );
    if ( !isValid_.load( std::memory_order_seq_cst ) )
    {
        std::cerr << "multiplyMatricesParallel invalidated\n";
        return;
    }

    result = threads::multiplyMatricesParallel( lhs, rhs, threadsCount );
#ifdef DEBUG
    std::cout << "Result matrix (parallel)\n";
    common::Matrix::write( result, std::cout );
#endif // DEBUG

    storeAtomicBool( writeAllowed_, true );
} // multiplyMatricesParallel


void threads::Tasks::writeResultMatrix( const common::Matrix& result )
{
    waitForAtomicBool( writeAllowed_, true );
    if ( !isValid_.load() )
    {
        std::cerr << "writeResultMatrix invalidated\n";
        return;
    }

    /// Вывод результата в файл
    std::ofstream outStream( common::defs::outFile, std::ios_base::out | std::ios_base::trunc );
    if ( !outStream.is_open() )
    {
        std::cerr << "Cannot open file " << common::defs::outFile << '\n';
        return;
    }
    if ( !common::Matrix::write( result, outStream ) )
    {
        std::cerr << "Could not write result matrix\n";
        return;
    }
} // writeResultMatrix


void threads::Tasks::invalidate()
{
    storeAtomicBool( isValid_, false );
} // invalidate


void threads::Tasks::storeAtomicBool( std::atomic< bool >& atomic, bool value )
{
    atomic.store( value, std::memory_order_seq_cst );
} // storeAtomicBool


void threads::Tasks::waitForAtomicBool( const std::atomic< bool >& atomic, bool value )
{
    while ( isValid_.load( std::memory_order_seq_cst ) 
            && value != atomic.load( std::memory_order_seq_cst ) )
    {
        ; // spinlock
    }
} // waitForAtomicBool
