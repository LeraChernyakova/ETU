#include <iostream>
#include <map>
#include <string>
#include <cstdint>

#include "matrix.h"
#include "algorithms.h"


enum class MultiplicationMode
{
      Serial
    , Parallel
    , Strassen
    , CheckAll
    , Invalid
};

constexpr size_t multiplicationThreads = 7;

int main( int argc, char** argv )
{
    static const std::map< std::string, MultiplicationMode > modeMap = {
          { "serial", MultiplicationMode::Serial }
        , { "parallel", MultiplicationMode::Parallel }
        , { "strassen", MultiplicationMode::Strassen }
        , { "check-all", MultiplicationMode::CheckAll }
    };

    constexpr char usage[] = "Usage: <program> {serial|parallel|strassen|check-all} <size> [debug]\n";

    MultiplicationMode mode = MultiplicationMode::Invalid;
    size_t matrixSize = 0;
    bool debug = false;

    if ( argc > 2 && argc < 5 )
    {
        const std::string modeStr{ argv[ 1 ] };
        if ( 0 == modeMap.count( modeStr ) )
        {
            std::cerr << usage;
            return 1;
        }
        mode = modeMap.at( modeStr );
        try
        {
            matrixSize = std::stoull( argv[ 2 ], nullptr, 10 );
        }
        catch ( const std::exception& )
        {
            std::cerr << usage;
            return 1;
        }
        if ( argc == 4 && "debug" == std::string{ argv[ 3 ] } )
        {
            debug = true;
        }
    }
    else
    {
        std::cerr << usage;
        return 1;
    }

    lab4::Matrix< int > lhs{ matrixSize, matrixSize };
    lab4::Matrix< int > rhs{ matrixSize, matrixSize };
    lhs.RandomFill( 0, 10 );
    rhs.RandomFill( 0, 10 );

    switch( mode )
    {
        case MultiplicationMode::Serial:
        {
            lab4::Matrix< int > result = lab4::Algorithms< int >::MultiplicationSerial( lhs, rhs );
            if ( debug )
            {
                result.Print( std::cout );
            }
            break;
        }
        case MultiplicationMode::Parallel:
        {
            lab4::Matrix< int > result = lab4::Algorithms< int >::MultiplicationParallel( lhs, rhs, multiplicationThreads );
            if ( debug )
            {
                result.Print( std::cout );
            }
            break;
        }
        case MultiplicationMode::Strassen:
        {
            lab4::Matrix< int > result{ lhs.GetRows(), rhs.GetCols() };
            lab4::Algorithms< int >::MultiplicationStrassen( lhs, rhs, result );
            if ( debug )
            {
                result.Print( std::cout );
            }
            break;
        }
        case MultiplicationMode::CheckAll:
        {
            lab4::Matrix< int > resultSerial = lab4::Algorithms< int >::MultiplicationSerial( lhs, rhs );
            lab4::Matrix< int > resultParallel = lab4::Algorithms< int >::MultiplicationParallel( lhs, rhs, multiplicationThreads );
            lab4::Matrix< int > resultStrassen{ lhs.GetRows(), rhs.GetCols() };
            lab4::Algorithms< int >::MultiplicationStrassen( lhs, rhs, resultStrassen );
            if ( debug )
            {
                resultSerial.Print( std::cout );
                resultParallel.Print( std::cout );
                resultStrassen.Print( std::cout );
            }

            if ( !( resultSerial == resultParallel ) )
            {
                std::cerr << "Serial and parallel results does not match\n";
                return 1;
            }
            if ( !( resultSerial == resultStrassen ) )
            {
                std::cerr << "Serial and strassen results does not match\n";
                return 1;
            }
            break;
        }
        default: ///< never here
        return 1;
    }
    
    return 0;
}
