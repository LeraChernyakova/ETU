#include <matrix_slice.h>

#include <cassert>

MatrixSlice::MatrixSlice( const Matrix& matr, size_t start_row, size_t start_col, size_t rows, size_t cols ):
     matr_{ matr }, start_row_{ start_row },
     start_col_{ start_col }, rows_{ rows }, cols_{ cols }
{}


MatrixSlice::MatrixSlice( const Matrix& matr ):
     matr_{ matr }, start_row_{ 0 }, start_col_{ 0 },
     rows_{ matr.get_rows() }, cols_{ matr.get_cols() }
{}


size_t MatrixSlice::get_rows() const
{
     return rows_;
}


size_t MatrixSlice::get_cols() const
{
     return cols_;
}


MatrixSlice::operator Matrix() const
{
     Matrix result{ rows_, cols_ };
     for ( size_t i = 0; i < rows_; i++ )
     {
          for ( size_t j = 0; j < cols_; j++ )
          {
               result.get( i, j ) = get( i, j );
          }
     }
     return result;
}


float MatrixSlice::get( size_t i, size_t j ) const
{
     return matr_.get( start_row_ + i, start_col_+ j );
}


Matrix operator+( const MatrixSlice& lhs, const MatrixSlice& rhs )
{
     assert( lhs.get_cols() == rhs.get_cols() );
     assert( lhs.get_rows() == rhs.get_rows() );

     Matrix result{ lhs.get_cols(), rhs.get_cols() };
     for ( size_t i = 0; i < lhs.get_rows(); i++ )
     {
          for ( size_t j = 0; j < lhs.get_cols(); j++ )
          {
               result.get( i, j ) = lhs.get( i, j ) + rhs.get( i, j );
          }
     }
     return result;
}


Matrix operator-( const MatrixSlice& lhs, const MatrixSlice& rhs )
{
     assert( lhs.get_cols() == rhs.get_cols() );
     assert( lhs.get_rows() == rhs.get_rows() );

     Matrix result{ lhs.get_cols(), rhs.get_cols() };
     for ( size_t i = 0; i < lhs.get_rows(); i++ )
     {
          for ( size_t j = 0; j < lhs.get_cols(); j++ )
          {
               result.get( i, j ) = lhs.get( i, j ) - rhs.get( i, j );
          }
     }
     return result;
}


Matrix operator*( const MatrixSlice& lhs, const MatrixSlice& rhs )
{
     assert( lhs.get_cols() == rhs.get_cols() );
     assert( lhs.get_rows() == rhs.get_rows() );

     Matrix result{ lhs.get_rows(), rhs.get_cols() };
     for ( size_t i = 0; i < lhs.get_rows(); i++ )
     {
          for ( size_t j = 0; j < rhs.get_cols(); j++ )
          {
               for ( size_t k = 0; k < lhs.get_rows(); k++ )
               {
                    result.get( i, j ) = lhs.get( i, k ) - rhs.get( k, j );
               }
          }
     }
     return result;
}
