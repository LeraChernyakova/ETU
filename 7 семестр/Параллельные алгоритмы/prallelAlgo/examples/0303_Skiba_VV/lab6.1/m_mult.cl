#define MAX_BS 16

__kernel void matrix_multiply(__global float* A, __global float* B, __global float* C, int size, int block_size)
{
    const int lr = get_local_id(0);  // local_row
    const int lc = get_local_id(1);  // local_col
    const int gr = get_global_id(0);  // global_row
    const int gc = get_global_id(1);  // global_col

    __local float Asub[MAX_BS][MAX_BS];
    __local float Bsub[MAX_BS][MAX_BS];


    float sum = 0;
    const int block_num = size / block_size;

    for (int b = 0; b < block_num; b++) {
        Asub[lr][lc] = A[gr * size + b * block_size + lc];
        Bsub[lr][lc] = B[b * block_size * size + lr * size + gc];

        barrier(CLK_LOCAL_MEM_FENCE);

        for (int k = 0; k < block_size; ++k) {
            sum += Asub[lr][k] * Bsub[k][lc];
        }

        barrier(CLK_LOCAL_MEM_FENCE);
    }

    C[gr * size + gc] = sum;
}