#define SUBMATRIX_SIZE 16

__kernel void mult_matrix(__global int* matrix1, __global int* matrix2, __global int* res, int size) {
    const int loc_row = get_local_id(0);
    const int loc_col = get_local_id(1);
    const int gl_row = get_global_id(0);
    const int gl_col = get_global_id(1);

    __local int submatrix1[SUBMATRIX_SIZE][SUBMATRIX_SIZE];
    __local int submatrix2[SUBMATRIX_SIZE][SUBMATRIX_SIZE];

    int sum = 0;
    const int submatrix_num = size / SUBMATRIX_SIZE;
    for (int i = 0; i < submatrix_num; i++) {
        submatrix1[loc_row][loc_col] = matrix1[gl_row * size + i * SUBMATRIX_SIZE + loc_col];
        submatrix2[loc_row][loc_col] = matrix2[loc_row * size + i * SUBMATRIX_SIZE * size + gl_col];

        barrier(CLK_LOCAL_MEM_FENCE);

        for (int k = 0; k < SUBMATRIX_SIZE; k++) {
            sum += submatrix1[loc_row][k] * submatrix2[k][loc_col];
        }

        barrier(CLK_LOCAL_MEM_FENCE);
    }

    res[gl_row * size + gl_col] = sum;
}