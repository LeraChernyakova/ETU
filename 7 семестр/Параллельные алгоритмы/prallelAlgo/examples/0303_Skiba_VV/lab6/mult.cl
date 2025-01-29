__kernel void matrix_multiply(const int M, const int N, const int P,
                              __global float* A, __global float* B, __global float* C) {
    int row = get_global_id(0);
    int col = get_global_id(1);

    if (row < M && col < P) {
        float sum = 0.0;
        for (int k = 0; k < N; k++) {
            sum += A[row * N + k] * B[k * P + col];
        }
        C[row * P + col] = sum;
    }
}