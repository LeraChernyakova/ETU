__kernel void mandelbrot( __global char *out )
{
     const size_t max_iters = 1000;
     const float x_scale[ 2 ] = { -2.0f , 0.47f };
     const float y_scale[ 2 ] = { -1.12f, 1.12f };

     size_t i = get_global_id( 0 );
     size_t j = get_global_id( 1 );
     size_t width = get_global_size( 0 );
     size_t height = get_global_size( 1 );

     float x0 = i * ( x_scale[ 1 ] - x_scale[ 0 ] ) / width + x_scale[ 0 ];
     float y0 = j * ( y_scale[ 1 ] - y_scale[ 0 ] ) / height + y_scale[ 0 ];
     float x2 = 0.0f, y2 = 0.0f, w = 0.0f;
     size_t iter = 0;
     for ( ; x2 + y2 <= 4 && iter < max_iters; iter++ )
     {
          float x = x2 - y2 + x0;
          float y = w - x2 - y2 + y0;
          x2 = x * x;
          y2 = y * y;
          w = ( x + y ) * ( x + y );
     }

     int pixel_pos = 3 * ( i + j * width );
     out[ pixel_pos + 0 ] = ( char )( 1.0f / atan( iter * 1.0f / max_iters ) * 255 );
     out[ pixel_pos + 1 ] = ( char )( sin( iter * 1.0f / max_iters ) * 255 );
     out[ pixel_pos + 2 ] = ( char )( 1.0f / atan( iter * 1.0f / max_iters ) * 255 );
}