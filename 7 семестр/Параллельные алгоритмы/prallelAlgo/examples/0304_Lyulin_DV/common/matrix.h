#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <ostream>
#include <thread>

class Matrix
{
public:
     static constexpr int output_precision = 3;
     static constexpr float compare_precision = 0.001;
     friend bool operator==( const Matrix&, const Matrix& );

     Matrix( size_t rows = 0, size_t cols = 0 );
     Matrix( const Matrix& other ) = default;
     Matrix( Matrix&& other ) = default;
     Matrix& operator=( const Matrix& rhs ) = default;
     Matrix& operator=( Matrix&& rhs ) = default;

     float get( size_t i, size_t j ) const;
     float& get( size_t i, size_t j );

     size_t get_cols() const;
     size_t get_rows() const;

     void insert_part( const Matrix& matr, size_t row, size_t col );
     const float *data() const;
     float *data();

     static Matrix generate( size_t i, size_t j );

private:
     static constexpr float rand_min = -2.0f;
     static constexpr float rand_max = 2.0f;

     size_t rows_;
     size_t cols_;
     std::vector< float > data_;
};


Matrix operator*( const Matrix& lhs, const Matrix& rhs );
std::ostream& operator<<( std::ostream& lhs, const Matrix& rhs );
bool operator==( const Matrix& lhs, const Matrix& rhs );

Matrix multiply_matrices_strassen( const Matrix& lhs, const Matrix& rhs );
Matrix multiply_matrices_parallel_v1( const Matrix& lhs, const Matrix& rhs,
     size_t thread_count = static_cast< size_t >( std::thread::hardware_concurrency() ) );
Matrix multiply_matrices_parallel_v2( const Matrix& lhs, const Matrix& rhs,
     size_t thread_count = static_cast< size_t >( std::thread::hardware_concurrency() ) );

#endif // MATRIX_H

