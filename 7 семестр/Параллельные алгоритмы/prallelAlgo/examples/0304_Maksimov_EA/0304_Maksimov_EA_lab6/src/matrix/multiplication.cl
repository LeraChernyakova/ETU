#define SUB_SIZE 32

__kernel void multiplication(
    __global int* A,
    __global int* B,
    __global int* result,
    int N
) {
    const int localRow = get_local_id(0);
    const int localColumn = get_local_id(1);
    const int globalRow = get_global_id(0);
    const int globalColumn = get_global_id(1);

    __local int tileA[SUB_SIZE][SUB_SIZE];
    __local int tileB[SUB_SIZE][SUB_SIZE];

    int sum = 0;
    const int blockNumber = N / SUB_SIZE;

    for (int i = 0; i < blockNumber; i++) {
        // Загружаем тайлы матрицы
        tileA[localRow][localColumn] = A[globalRow*N + i*SUB_SIZE + localColumn];
        tileB[localRow][localColumn] = B[localRow*N + i*SUB_SIZE*N + globalColumn];

        // Ожидаем завершение загрузки
        barrier(CLK_LOCAL_MEM_FENCE);

        // Умножение
        for (int j = 0; j < SUB_SIZE; j++) {
            sum += tileA[localRow][j] * tileB[j][localColumn];
        }

        // Для синхронизации со следующим блоком
        barrier(CLK_LOCAL_MEM_FENCE);
    }

    result[globalRow*N + globalColumn] = sum;
}
