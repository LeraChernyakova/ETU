
__kernel void matrix_multiply(__global int* result, __global int* first_matrix, __global int* second_matrix, int size) {

    const int tile_size = 32;

    // Getting position of current work-item relative to the work group
    int2 local_pos = (int2)(get_local_id(1), get_local_id(0));
    int2 global_pos = (int2)(tile_size * get_group_id(1) + local_pos.x, tile_size * get_group_id(0) + local_pos.y);
    // int2 global_pos = tile_size * (int2)(get_group_id(0), get_group_id(1)) + local_pos;

    // Using (allocating) local arrays for tile store
    __local int a_tile[tile_size][tile_size];
    __local int b_tile[tile_size][tile_size];


    float value = 0;

    const int tiles_count = size / tile_size;
    for (int i = 0; i < tiles_count; ++i)
    {
        // Load one element to each tile
        const int row = tile_size * i + local_pos.x;
        const int column = tile_size * i + local_pos.y;

        a_tile[local_pos.y][local_pos.x] = first_matrix[global_pos.y * size + row];
        b_tile[local_pos.y][local_pos.x] = second_matrix[column * size + global_pos.x];

        // Wait for all work-items withing work-group to finish loading each tile elements
        barrier(CLK_LOCAL_MEM_FENCE);

        // Performing multiplications
        for (int j = 0; j < tile_size; j++) {
            value += a_tile[local_pos.y][j] * b_tile[j][local_pos.x];
        }

        // Wait for all of them to finish before loading next pair
        barrier(CLK_LOCAL_MEM_FENCE);
    }

    // Write results
    result[global_pos.y * size + global_pos.x] = value;
}
