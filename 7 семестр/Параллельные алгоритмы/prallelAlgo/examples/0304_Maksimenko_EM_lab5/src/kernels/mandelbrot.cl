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


__kernel void calculate( int iterations, int width, int height, __global char* out )
{
    const size_t alWidth = get_global_size( 0 );

    const size_t x = get_global_id( 0 );
    const size_t y = get_global_id( 1 );

    const double zxMin = -2.0000;
    const double zyMin = -1.2000;
    const double zxMax =  1.0000;
    const double zyMax =  1.2000;

    const double stepX = ( zxMax - zxMin ) / width;
    const double stepY = ( zyMax - zyMin ) / height;

    double zx = zxMin + x * stepX;
    double zy = zyMin + y * stepY;
    size_t iteration = MakeIteration( zx, zy, iterations );
    out[ x + y * alWidth ] = ( char )( 0xFF - 0xFF * ( iteration / ( double )iterations ) );
} // calculate
