__kernel void matrixMult(const uint N,
                      const __global uint* A,
                      const __global uint* B,
                      __global uint* C) {
    
    const uint globalRow = get_global_id(0); 
    const uint globalCol = get_global_id(1); 
 
    uint acc = 0;
    for (uint k = 0; k < N; k++) {
        acc += A[k*N + globalRow] * B[globalCol*N + k];
    }
    C[globalCol*N + globalRow] = acc;
}