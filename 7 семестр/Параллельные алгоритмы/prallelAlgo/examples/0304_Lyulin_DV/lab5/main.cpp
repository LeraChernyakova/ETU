#include <iostream>
#include <chrono>
#include <cstdlib>
#include <cmath>

#include <utils.h>
#include <window.h>
#include <cl_func.h>

namespace
{

constexpr size_t channels = 3;

} // settings


void mandelbrot_calc( uint8_t *buffer, size_t width, size_t height, size_t channels )
{
     constexpr size_t max_iters = 1000;
     constexpr float x_scale[] = { -2.0f , 0.47f };
     constexpr float y_scale[] = { -1.12f, 1.12f };

     for ( size_t i = 0; i < width; i++ )
     {
          for ( size_t j = 0; j < height; j++ )
          {
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

               size_t pixel_pos = ( j * width + i ) * channels;
               buffer[ pixel_pos + 0 ] = static_cast< uint8_t >( 1.0f / std::atan( iter * 1.0f / max_iters ) * 255 );
               buffer[ pixel_pos + 1 ] = static_cast< uint8_t >( std::sin( iter * 1.0f / max_iters ) * 255 );
               buffer[ pixel_pos + 2 ] = static_cast< uint8_t >( 1.0f / std::atan( iter * 1.0f / max_iters ) * 255 );
          }
     }
}


int main( int argc, char const *argv[] )
{
     size_t width, height, aligned_width, aligned_height;
     if ( argc != 4 || !str_to_size( argv[ 2 ], width ) || !str_to_size( argv[ 3 ], height ) )
     {
          std::cout << "Usage: " << argv[ 0 ] << " [cpu|ocl] <width> <height>\n";
          return EXIT_FAILURE;
     }
     auto align = []( size_t x, size_t bound ){ return ( x + bound - 1 ) / bound * bound; };
     aligned_width = align( width, local_work_size[ 0 ] );
     aligned_height = align( height, local_work_size[ 1 ] );

     auto buffer = std::make_unique< uint8_t[] >( aligned_width * aligned_height * channels );

     auto t1 = std::chrono::high_resolution_clock::now();
     if ( std::string( argv[ 1 ] ) == "cpu" )
     {
          mandelbrot_calc( buffer.get(), aligned_width, aligned_height, channels );
     }
     else if ( std::string( argv[ 1 ] ) == "ocl" )
     {
          mandelbrot_ocl_calc( buffer.get(), aligned_width, aligned_height, channels );
     }
     else
     {
          std::cout << "Usage: " << argv[ 0 ] << " [cpu|ocl] <width> <height>\n";
          return EXIT_FAILURE;
     }
     auto t2 = std::chrono::high_resolution_clock::now();
     std::cout << "Time elapsed: "
          << std::chrono::duration< double, std::milli >( t2 - t1 ).count()
          << " ms\n";

     Window window( width, height, "Mandelbrot set" );
     window.show();
     window.set_buffer( buffer.get(), aligned_width, aligned_height );

	return Fl::run();
}
