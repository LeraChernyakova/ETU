size_t MakeIteration(double zx, double zy, size_t maxIter)
{
    size_t iter = 0;
    double zxCur = zx;
    double zyCur = zy;

    while((zxCur * zxCur + zyCur * zyCur <= 4.0) && (iter < maxIter)) {
        double zxPrev = zxCur;
        zxCur = zxCur * zxCur - zyCur * zyCur + zx;
        zyCur = 2 * zxPrev * zyCur + zy;
        iter++;
    }

    return iter;
}

__kernel void calculate(int iterations, int width, int height, __global char* out)
{
    const size_t alWidth = get_global_size(0);

    const size_t x = get_global_id(0);
    const size_t y = get_global_id(1);

    constexpr double zxMin = -2.0;
    constexpr double zyMin = -1.2;
    constexpr double zxMax =  1.0;
    constexpr double zyMax =  1.2;
    const double stepX = (zxMax - zxMin) / width;
    const double stepY = (zyMax - zyMin) / height;

    double zx = zxMin + x * stepX;
    double zy = zyMin + y * stepY;

    size_t iter = MakeIteration(zx, zy, iterations);
    out[x + y * alWidth] = (char)(0xFF - 0xFF * (iter / (double)iterations));
}
