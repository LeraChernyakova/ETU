// Computes the Mandelbrot Set to N Iterations
__kernel void mandelbrot(__global float const * real,
                        __global float const * imag,
                        int iterations,
                        __global int * answer) {
    // Получаем глобальный индекс.
    unsigned int gid = get_global_id(0);

    float x = real[gid]; // Реальная компонента.
    float y = imag[gid]; // Мнимая компонента.
    int n = 0; // Количество итераций.

    // Вычисляем фрактал Мальденброта.
    for (n = 0; (x*x + y*y <= 2*2) && (n < iterations); n++) {
        float x_temp = x*x - y*y + real[gid];
        y = 2*x*y + imag[gid];
        x = x_temp;
    }

    // Записываем вычисленное значение.
    answer[gid] = (x*x + y*y <= 2*2) ? -1 : n;
}