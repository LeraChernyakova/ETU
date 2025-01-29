int compute_iterations(const float x0, const float y0, int iterations) {
    int n = 0;
    for (float x = x0, y = y0; (x * x + y * y <= 2 * 2) && n < iterations; n++) { // расчёт количества итераций в зависимости от принадлежноати точек
        float xtemp = x * x - y * y + x0;
        y = 2 * x * y + y0;
        x = xtemp;
    }
    return n;
} 


unsigned int compute_color(int total_iters, float max_iters) { // раскраска в зависимости от количества итераций
    float min_iters = max_iters - 50;
    int pos =  255 * max(0.f, total_iters - min_iters) / (max_iters - min_iters);
    int red = 0;
    int green = 0;
    int blue = (int)(pos);
    return red | (green << 8) | (blue << 16); 
}


__kernel void mandelbrot(
    float max_iters,
    int w,
    int h,
    __global unsigned int * result
) { // передаём кол-во итераций, а также ширину и высоту изображения
    // позиция work item
    int ix = get_global_id(0);
    int iy = get_global_id(1); // за какой пиксель отвечает work item

    if (ix < w && iy < h) { // если в пределах изображения
        float x = 5.0f * (float)((ix - w / 2)) / w; // получаем координаты точки множества мандельброта
        float y = 5.0f * (float)((iy - h / 2)) / h;

        int total_iters = compute_iterations(x, y, (int)max_iters); // посчитать степень принадлежности к множеству мандельброта
        result[iy * w + ix] = compute_color(total_iters, max_iters); // раскрась степень
    }
}