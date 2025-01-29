__kernel void mandelbrot(__global char *out, int maxIters)
{
     const float xScale[2] = {-2.0f , 0.47f};
     const float yScale[2] = {-1.12f, 1.12f};

     size_t i = get_global_id(0);
     size_t j = get_global_id(1);
     size_t width = get_global_size(0);
     size_t height = get_global_size(1);

     float x0 = i * (xScale[1] - xScale[0]) / width + xScale[0];
     float y0 = j * (yScale[1] - yScale[0]) / height + yScale[0];
     float x2 = 0.0f, y2 = 0.0f, w = 0.0f;
     size_t iter = 0;
     for (; x2 + y2 <= 4 && iter < maxIters; iter++)
     {
          float x = x2 - y2 + x0;
          float y = w - x2 - y2 + y0;
          x2 = x * x;
          y2 = y * y;
          w = (x + y) * (x + y);
     }

     int pixelPos = 3 * (i + j * width);
     out[pixelPos + 0] = (int)(1.0f / atan(iter * 1.0f / maxIters) * 255);
     out[pixelPos + 1] = (int)(1.0f / atan(iter * 1.0f / maxIters) * 255);
     out[pixelPos + 2] = (int)(cos(iter * 1.0f / maxIters) * 255);
}