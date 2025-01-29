__kernel void mult(__global int* A, __global int* B,
                          __global int* C, int size) {
    const int lr = get_local_id(0);  // local_row
    const int lc = get_local_id(1);  // local_col
    const int gr = get_global_id(0);  // global_row 
    const int gc = get_global_id(1);  // global_col 
    __local int Asub[BS][BS];
    __local int Bsub[BS][BS];


    int sum = 0;
    const int block_num = size / BS;
    for (int b = 0; b < block_num; b++) {
        Asub[lr][lc] = A[gr * size + b * BS + lc]; // запись в локальную память
        Bsub[lr][lc] = B[lr * size + b * BS * size + gc]; // запись в локальную память

        barrier(CLK_LOCAL_MEM_FENCE); // синхронизация потоков

        for (int k = 0; k < BS; k++) {
            sum += Asub[lr][k] * Bsub[k][lc];
        }

        barrier(CLK_LOCAL_MEM_FENCE);
    }

    C[gr * size + gc] = sum;
}