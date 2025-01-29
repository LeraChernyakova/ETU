#define SUB_SIZE 32

__kernel void matrix_mult(__global int* A, __global int* B, __global int* C, int size) {
    const int lr = get_local_id(0);
    const int lc = get_local_id(1);
    const int gr = get_global_id(0);
    const int gc = get_global_id(1);  
    __local int Asub[SUB_SIZE][SUB_SIZE];
    __local int Bsub[SUB_SIZE][SUB_SIZE];


    int sum = 0;
    const int block_num = size / SUB_SIZE;
    for (int b = 0; b < block_num; b++) {
        Asub[lr][lc] = A[gr * size + b * SUB_SIZE + lc];
        Bsub[lr][lc] = B[lr * size + b * SUB_SIZE * size + gc];

        barrier(CLK_LOCAL_MEM_FENCE);

        for (int k = 0; k < SUB_SIZE; k++) {
            sum += Asub[lr][k] * Bsub[k][lc];
        }

        barrier(CLK_LOCAL_MEM_FENCE);
    }

    C[gr * size + gc] = sum;
}
