#include "ocl_matrices_multiplication.h"
#include <iostream>
#include <chrono>
#include <random>

// #define DEBUG

int main()
{
    constexpr size_t lhs_w  = 2048;
    constexpr size_t common = 2048;
    constexpr size_t rhs_h  = 2048;

    auto start = std::chrono::high_resolution_clock::now();

    std::unique_ptr< int32_t[] > lhs = std::make_unique< int32_t[] >( lhs_w * common );
    std::unique_ptr< int32_t[] > rhs = std::make_unique< int32_t[] >( common * rhs_h );

    for ( size_t i = 0; i < lhs_w * common; ++i )
    {
        lhs[ i ] = i % 32;
    }

    for ( size_t i = 0; i < rhs_h * common; ++i )
    {
        rhs[ i ] = i % 32;
    }

    ocl::OclMatricesMultiplication mult;
    mult.init( lhs_w, common, rhs_h, lhs.get(), rhs.get() );
    std::unique_ptr< int32_t[] > res = mult.process();
    mult.deinit();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast< std::chrono::milliseconds >( end - start ).count() << std::endl;

#if defined( DEBUG )
    for ( size_t y = 0; y < rhs_h; ++y )
    {
        for ( size_t x = 0; x < lhs_w; ++x )
        {
            std::cout << res[ x + y * lhs_w ] << " ";
        }
        std::cout << '\n';
    }
#endif // defined( DEBUG )
    return 0;
}
