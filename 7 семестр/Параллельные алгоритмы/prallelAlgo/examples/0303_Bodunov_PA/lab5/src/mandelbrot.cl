uint to_color_gray(int total_iters, float max_iters) {
    float min_iters = max_iters - 50;
    int pos = 0xff * max(0.f, total_iters - min_iters) / (max_iters - min_iters);
    return pos | (pos << 8) | (pos << 16) | (0xff << 24);
}



int compute_iterations(const float x0, const float y0, int iterations) {
    int n = 0;

    for(float x = x0, y = y0; (x * x + y * y <= 2 * 2) && n < iterations; n++) {
        float xtemp = x * x - y * y + x0;
        y = 2 * x * y + y0;
        x = xtemp;
    }

    return n;
}


__kernel void mandelbrot(float px, float py, float mag, int max_iters,
                         int w, int h, __global uint * result, int result_step) {
    int ix = get_global_id(0);
    int iy = get_global_id(1);

    if (ix < w && iy < h) {
        float x = px + mag * (float)((ix - w/2)) / w;
        float y = py + mag * (float)((iy - h/2)) / w;

        int total_iters = compute_iterations(x, y, (int)max_iters);
        result[iy * result_step + ix] = to_color_gray(total_iters, max_iters);
    }
}