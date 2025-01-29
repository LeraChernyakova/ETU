int compute_iterations(const float x0, const float y0, int iterations) {
    int n = 0;
    for (float x = x0, y = y0; (x * x + y * y <= 2 * 2) && n < iterations; n++) { 
        float xtemp = x * x - y * y + x0;
        y = 2 * x * y + y0;
        x = xtemp;
    }
    return n;
} 


unsigned int color(int total_iters, float max_iters) {
    float min_iters = max_iters - 50;
    int pos =  255 * max(0.f, total_iters - min_iters) / (max_iters - min_iters);
    return pos | (pos << 8) | (pos << 16); 
}


__kernel void mandelbrot(float max_iters, int w, int h, __global unsigned int * result) { 
    int ix = get_global_id(0);
    int iy = get_global_id(1); 

    if (ix < w && iy < h) {
        float x = 5.0f * (float)((ix - w / 2)) / w; 
        float y = 5.0f * (float)((iy - h / 2)) / h;

        int total_iters = compute_iterations(x, y, (int)max_iters); 
        result[iy * w + ix] = color(total_iters, max_iters);
    }
}