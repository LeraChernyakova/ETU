#include "mandelbrot.h"

#include <QPen>
#include <QPainter>

namespace // anonymous
{

size_t MakeIteration( double zx, double zy, size_t maxIteration )
{
    size_t iteration = 0;
    double zxCurrent = zx;
    double zyCurrent = zy;

    while ( ( zxCurrent * zxCurrent + zyCurrent * zyCurrent <= 4.0 ) && ( iteration < maxIteration ) )
    {
        double zxPrevious = zxCurrent;
        zxCurrent = zxCurrent * zxCurrent - zyCurrent * zyCurrent + zx;
        zyCurrent = 2 * zxPrevious * zyCurrent + zy;
        ++iteration;
    }

    return iteration;
} // MakeIteration

} // anonymous namespace


Mandelbrot::Mandelbrot( size_t w, size_t h, size_t iterations )
    : width_{ w }
    , height_{ h }
    , iterations_{ iterations }
    , points_{ std::make_unique< uint8_t[] >( w  * h ) }
    , image_{ static_cast< int >( w ), static_cast< int >( h ), QImage::Format_RGB888 }
{} // Mandelbrot


const QImage& Mandelbrot::Image() const
{
    return image_;
} // Image


void Mandelbrot::Generate()
{
    constexpr double zxMin = -2.0000;
    constexpr double zyMin = -1.2000;
    constexpr double zxMax =  1.0000;
    constexpr double zyMax =  1.2000;
    const double stepX = ( zxMax - zxMin ) / width_;
    const double stepY = ( zyMax - zyMin ) / height_;

    double zx = zxMin;
    for ( size_t x = 0; x < width_; ++x, zx += stepX )
    {
        double zy = zyMin;
        for ( size_t y = 0; y < height_; ++y, zy += stepY )
        {
            size_t iteration = MakeIteration( zx, zy, iterations_ );
            points_[ x + y * width_ ] = static_cast< uint8_t >(
                0xff - 0xff * ( iteration / static_cast< double >( iterations_ ) ) );
        }
    }
} // Generate


void Mandelbrot::FillImage()
{
    QPainter painter;
    painter.begin( &image_ );

    for ( size_t x = 0; x < width_; ++x )
    {
        for ( size_t y = 0; y < height_; ++y )
        {
            QPen pen( static_cast< uint8_t >( 0xff *
                ( points_[ x + y * width_ ] / static_cast< double >( iterations_ ) ) ) << 21 );
            painter.setPen( pen );
            painter.drawPoint( x, y );
        }
    }

    painter.end();
} // FillImage
