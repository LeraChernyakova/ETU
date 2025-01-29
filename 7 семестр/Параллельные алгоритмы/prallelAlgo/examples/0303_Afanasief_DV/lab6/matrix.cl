__kernel void matrix(
    __global int* left,
    __global int* right,
    __global int* result,
    int size
) {
    const int local_size = 16;
    const int local_col = get_local_id(0);
    const int local_row = get_local_id(1);
    const int global_col = local_size * get_group_id(0) + local_col;
    const int global_row = local_size * get_group_id(1) + local_row;

    __local int left_tile[local_size][local_size];
    __local int right_tile[local_size][local_size];

    int sum = 0;

    const int tiles_in_line = size / local_size;

    for (int i = 0; i < tiles_in_line; i++) {

        const int tiled_row = local_size * i + local_row;
        const int tiled_col = local_size * i + local_col;

        left_tile[local_row][local_col] = left[global_row * size + tiled_col];
        right_tile[local_row][local_col] = right[tiled_row * size + global_col];

        barrier(CLK_LOCAL_MEM_FENCE);

        for (int j = 0; j < local_size; j++) {
            sum += (left_tile[local_row][j] * right_tile[j][local_col]);
        }
        barrier(CLK_LOCAL_MEM_FENCE);
    }
    result[global_row * size + global_col] = sum;
}
