__kernel void matrix( __global const float *lhs, __global const float *rhs, __global float *out )
{
     const size_t tile_size = 16;
     const size_t matr_size = get_global_size( 0 );

     const size_t row = get_local_id( 0 );
     const size_t col = get_local_id( 1 );
     const size_t result_row = tile_size * get_group_id( 0 ) + row;
     const size_t result_col = tile_size * get_group_id( 1 ) + col;

     // Общая память workgroup для параллельного заполнения
     __local float lhs_sub[ tile_size ][ tile_size ];
     __local float rhs_sub[ tile_size ][ tile_size ];

     float dot_product = 0.0f;

     const size_t tile_count = matr_size / tile_size;
     for ( size_t i = 0; i < tile_count; i++ )
     {
          const size_t tiled_row = tile_size * i + row;
          const size_t tiled_col = tile_size * i + col;
          lhs_sub[ row ][ col ] = lhs[ result_row * matr_size + tiled_col ];
          rhs_sub[ row ][ col ] = rhs[ tiled_row * matr_size + result_col ];

          barrier( CLK_LOCAL_MEM_FENCE );
          for ( size_t j = 0; j < tile_size; j++ )
          {
               dot_product += lhs_sub[ row ][ j ] * rhs_sub[ j ][ col ];
          }
          barrier( CLK_LOCAL_MEM_FENCE );
     }

     out[ result_row * matr_size + result_col ] = dot_product;
}