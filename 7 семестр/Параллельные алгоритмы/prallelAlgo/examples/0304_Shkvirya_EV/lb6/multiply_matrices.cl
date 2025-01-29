__kernel void multiply_matrices(__global int* result, __global int* firstMatrix, __global int* secondMatrix, int size) {
    const int tileSize = 32;

    // Getting position of current work-item relative to the work group
    int2 localPos = (int2)(get_local_id(1), get_local_id(0));
    int2 globalPos = (int2)(tileSize * get_group_id(1) + localPos.x, tileSize * get_group_id(0) + localPos.y);

    // Using (allocating) local arrays for tile store
    __local int aTile[tileSize][tileSize];
    __local int bTile[tileSize][tileSize];

    float value = 0;

    const int tilesCount = size / tileSize;
    for (int i = 0; i < tilesCount; ++i)
    {
        // Load one element to each tile
        const int row = tileSize * i + localPos.x;
        const int column = tileSize * i + localPos.y;

        aTile[localPos.y][localPos.x] = firstMatrix[globalPos.y * size + row];
        bTile[localPos.y][localPos.x] = secondMatrix[column * size + globalPos.x];

        // Wait for all work-items withing work-group to finish loading each tile elements
        barrier(CLK_LOCAL_MEM_FENCE);

        // Performing multiplications
        for (int j = 0; j < tileSize; j++) {
            value += aTile[localPos.y][j] * bTile[j][localPos.x];
        }

        // Wait for all of them to finish before loading next pair
        barrier(CLK_LOCAL_MEM_FENCE);
    }

    // Write results
    result[globalPos.y * size + globalPos.x] = value;
}
