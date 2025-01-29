double myMax(double a, double b) {
    return a > b ? a : b;
}

int computeIterations(const float x0, const float y0, int iterations) {
    int n = 0;

    for (float x = x0, y = y0; (x*x + y*y <= 2*2) && n < iterations; n++) { 
        float xtemp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtemp;
    }
    
    return n;
}

unsigned int computeColor(int itersTotal, float itersMax) { 
    float itersMin = itersMax - 50;
    int pos = 255 * myMax(0.f, itersTotal-itersMin) / (itersMax-itersMin);

    int red = (int)(pos);
    int green = 0;
    int blue = 0;

    return red | (green << 8) | (blue << 16);
}

__kernel void mandelbrot(
    float itersMax,
    int w, int h,
    __global unsigned int* result
) { 
    int ix = get_global_id(0);
    int iy = get_global_id(1); 

    if ((ix < w) && (iy < h)) {
        float x = 5.0f * (float)((ix - w/2)) / w; 
        float y = 5.0f * (float)((iy - h/2)) / h;

        int itersTotal = computeIterations(x, y, (int)itersMax); 
        result[iy * w + ix] = computeColor(itersTotal, itersMax);
    }

    return;
}
