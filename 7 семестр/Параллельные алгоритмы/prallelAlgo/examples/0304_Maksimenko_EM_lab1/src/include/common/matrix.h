#ifndef COMMON_MATRIX_H
#define COMMON_MATRIX_H

#include <vector>
#include <cstddef>
#include <iosfwd>

namespace ipc
{

class Socket;

} // namespace ipc

namespace common
{

class Matrix final
{
public:
    Matrix( size_t rows, size_t columns );

    inline size_t   rows() const { return rows_; }
    inline size_t   columns() const { return columns_; }
    inline float*   data() { return data_.data(); }
    inline const float* data() const { return data_.data(); }

    float           get( size_t row, size_t column ) const;
    void            set( size_t row, size_t column, float el );

    static bool     read( Matrix& matrix, std::istream& stream );
    static bool     read( Matrix& matrix, ipc::Socket& socket );

    static bool     write( const Matrix& matrix, std::ostream& stream );
    static bool     write( const Matrix& matrix, ipc::Socket& socket );

    static float    multiplyRC( const Matrix& lhs, const Matrix& rhs, size_t row, size_t column );

private:
    size_t rows_;               ///< Количество строк в матрице.
    size_t columns_;            ///< Количество столбцов в матрице.
    std::vector< float > data_; ///< Элементы матрицы.
}; // class Matrix

} // namespace common

#endif // COMMON_MATRIX_H
