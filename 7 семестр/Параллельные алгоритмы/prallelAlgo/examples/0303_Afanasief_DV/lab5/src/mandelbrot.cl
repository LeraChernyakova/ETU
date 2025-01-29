bool isLastIter(const float x, const float y, const int iteration, const int iterLimit) {
    return x * x + y * y <= 4 && iteration < iterLimit;
}

float nextX(const float x, const float y, const float center) {
    return x * x - y * y + center;
}

float nextY(const float x, const float y, const float center) {
    return 2 * x * y + center;
}

int compute(const float centerX, const float centerY, int iterLimit) {
    int iteration = 0;
    float x = centerX;
    float y = centerY;

    while (isLastIter(x, y, iteration, iterLimit)) {
        float temp = nextX(x, y, centerX);
        y = nextY(x, y, centerY);
        x = temp;
        iteration++;
    }
    return iteration;
}

uint color(int iterations, int iterLimit) {
    int maxValue = 0xFF;
    int pos = maxValue * iterations / iterLimit;
    return pos | (pos << 8) | (pos << 16) | (maxValue << 24);
}

__kernel void computeMandelbrot(
    int height,
    int width,
    float ratio,
    int iterLimit,
    __global uint* buffer
) {
    int localX = get_global_id(0);
    int localY = get_global_id(1);

    if (localX < width && localY < height) {
        float x = ratio * (float) (localX - width / 2) / width;
        float y = ratio * (float) (localY - height / 2) / width;

        int iteration = compute(x, y, iterLimit);
        int index = localY * width + localX;
        buffer[index] = color(iteration, iterLimit);
    }
}
