__kernel void mandelbrot(
    __global uchar *image,
    int width,
    int height,
    float x0,
    float y0,
    float x1,
    float y1,
    int maxIterations) {

    int x = get_global_id(0);
    int y = get_global_id(1);

    if (x < width && y < height) {
        float dx = (x1 - x0) / width;
        float dy = (y1 - y0) / height;
        float real = x0 + dx * x;
        float imag = y0 + dy * y;
        int count = 0;
        float tempReal, tempImag, real2, imag2;

        for (int i = 0; i < maxIterations; ++i) {
            real2 = real * real;
            imag2 = imag * imag;
            if (real2 + imag2 > 4.0f) break;
            tempReal = real2 - imag2 + x0 + dx * x;
            tempImag = 2 * real * imag + y0 + dy * y;
            real = tempReal;
            imag = tempImag;
            count++;
        }

        image[y * width + x] = (uchar)(255 * count / maxIterations);
    }
}