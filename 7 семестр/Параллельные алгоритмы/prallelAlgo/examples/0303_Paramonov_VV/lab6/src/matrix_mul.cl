#include "utility/defines.hpp"


__kernel void matrix_mul (
    __global int const * first_mat, __global int const * second_mat,
    __global int * result_mat, int side
) {
    // Выделяем области локальной памяти.
    __local float first_fragment[WG_SIZE][WG_SIZE];
    __local float second_fragment[WG_SIZE][WG_SIZE];

    // Получаем значения строки и столбца, которые нужно вычислить у result_mat.
    int col = get_global_id(0);
    int row = get_global_id(1);
    int l_col = get_local_id(0);
    int l_row = get_local_id(1);

    float result_element = 0;

    for (int i = 0; i < (side / WG_SIZE); i++) {
        // Заполняем 1 элемент нового фрагмента умножаемых матриц (остальные заполнят другие work item).
        first_fragment[l_row][l_col] = first_mat[row*side + (i*WG_SIZE + l_col)];
        second_fragment[l_row][l_col] = second_mat[(i*WG_SIZE + l_row)*side + col];

        // Синхронизируем, чтобы first_fragment и second_fragment полностью загрузились в локальную память.
        barrier(CLK_LOCAL_MEM_FENCE);

        // Считаем частичный результат, который получается из фрагментов матриц first_mat и second_mat.
        for (int j = 0; j < WG_SIZE; j++) {
            result_element += first_fragment[l_row][j] * second_fragment[j][l_col];
        }
        // Ждем, пока все work item-ы закончат использовать фрагменты матриц в локальной памяти.
        barrier(CLK_LOCAL_MEM_FENCE);
    }

    // Записываем вычисленное значение.
    result_mat[row*side + col] = result_element;
}