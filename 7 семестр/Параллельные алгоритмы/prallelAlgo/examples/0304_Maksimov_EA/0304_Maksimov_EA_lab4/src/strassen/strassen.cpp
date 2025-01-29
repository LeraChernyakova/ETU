#include "strassen.h"

std::vector<Matrix> split(Matrix A) {
    int newSize = A.size()/2;
    std::vector<Matrix> matrices;
    for(int i = 0; i < 4; i++) {
        matrices.push_back(Matrix(newSize, std::vector<int>(newSize, 0)));
    }

    for(int i = 0; i < newSize; i++) {
        for(int j = 0; j < newSize; j++) {
            matrices[0][i][j] = A[i][j];
            matrices[1][i][j] = A[i][j+newSize];
            matrices[2][i][j] = A[i+newSize][j];
            matrices[3][i][j] = A[i+newSize][j+newSize];
        }
    }

    return matrices;
}

Matrix join(std::vector<Matrix> Cs) {
    int newSize = Cs[0].size();
    Matrix C = Matrix(newSize*2, std::vector<int>(newSize*2, 0));

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < newSize; j++) {
            for(int k = 0; k < newSize; k++) {
                C[(i/2)*newSize+j][(i%2)*newSize+k] = Cs[i][j][k];
            }
        }
    }

    return C;
}

void multiplyStrassenRoutine(std::vector<Matrix>* matrices, int recursionDepth = 1) {
    int inputMatricesSize = (*matrices)[0].size();
    if((inputMatricesSize < STRASSEN_MIN_SIZE) || (recursionDepth > STRASSEN_RECURSION_LIMIT)) {
        multiplyMatrices(matrices);
        return;
    }

    std::vector<Matrix> As = split((*matrices)[0]);     // A_11, A_12, A_21, A_22
    std::vector<Matrix> Bs = split((*matrices)[1]);     // B_11, B_12, B_21, B_22
    std::vector<std::vector<Matrix>> MsRaw = std::vector<std::vector<Matrix>>{
        std::vector<Matrix> {As[0]+As[3],   Bs[0]+Bs[3]},
        std::vector<Matrix> {As[1]-As[3],   Bs[2]+Bs[3]},
        std::vector<Matrix> {As[2]-As[0],   Bs[0]+Bs[1]},
        std::vector<Matrix> {As[0]+As[1],   Bs[3]},
        std::vector<Matrix> {As[2]+As[3],   Bs[0]},
        std::vector<Matrix> {As[3],         Bs[2]-Bs[0]},
        std::vector<Matrix> {As[0],         Bs[1]-Bs[3]},
    };
    
    int sizeMs = MsRaw.size();
    std::vector<std::thread> threads;
    for(int i = 0; i < sizeMs; i++) {
        threads.push_back(std::thread(multiplyStrassenRoutine, &MsRaw[i], recursionDepth+1));
    }
    for(int i = 0; i < sizeMs; i++) {
        threads[i].join();
    }

    std::vector<Matrix> Ms;
    for(int i = 0; i < sizeMs; i++) {
        Ms.push_back(MsRaw[i][2]);
    }
    std::vector<Matrix> Cs = std::vector<Matrix> {
        Ms[0]+Ms[1]+Ms[5]-Ms[3],
        Ms[6]+Ms[3],
        Ms[5]+Ms[4],
        Ms[0]+Ms[2]+Ms[6]-Ms[4]
    };

    (*matrices).push_back(join(Cs));

    return;
}

void multiplyStrassen(std::vector<Matrix>* matrices, int N) {
    // 1. Приведение матриц к размеру N=2^M.
    int fixedMatrixSize = 1 << int(std::ceil(std::log2(N)));
    if(N < fixedMatrixSize) {
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < N; j++) {
                (*matrices)[i][j].resize(fixedMatrixSize, 0);
            }
            (*matrices)[i].resize(fixedMatrixSize, std::vector<int>(fixedMatrixSize, 0));
        }
    }

    // 2. Выполнение алгоритма.
    multiplyStrassenRoutine(matrices);

    // 3. Обратое преобразование матрицы к исходному размеру.
    if(N < fixedMatrixSize) {
        (*matrices)[2].resize(N);
        for(int i = 0; i < N; i++) {
            (*matrices)[2][i].resize(N);
        }
    }
}
