#include "strassen_resolver.hpp"


void strassen_resolve(
    Matrix left,
    Matrix right,
    Matrix &result
) {
    int dimension = result.matrix.size() / 2;
    Matrix P1 = Matrix::empty_matrix(dimension);
    Matrix P2 = Matrix::empty_matrix(dimension);
    Matrix P3 = Matrix::empty_matrix(dimension);
    Matrix P4 = Matrix::empty_matrix(dimension);
    Matrix P5 = Matrix::empty_matrix(dimension);
    Matrix P6 = Matrix::empty_matrix(dimension);
    Matrix P7 = Matrix::empty_matrix(dimension);
    std::vector<std::thread> multipliers;
    std::vector<Matrix> left_splited = split(left);
    std::vector<Matrix> rigth_splited = split(right);
    multipliers.push_back(std::thread(resolve, left_splited[0] + left_splited[3], rigth_splited[0] + rigth_splited[3], std::ref(P1)));
    multipliers.push_back(std::thread(resolve, left_splited[2] + left_splited[3], rigth_splited[0], std::ref(P2)));
    multipliers.push_back(std::thread(resolve, left_splited[0], rigth_splited[1] - rigth_splited[3], std::ref(P3)));
    multipliers.push_back(std::thread(resolve, left_splited[3], rigth_splited[2] - rigth_splited[0], std::ref(P4)));
    multipliers.push_back(std::thread(resolve, left_splited[0] + left_splited[1], rigth_splited[3], std::ref(P5)));
    multipliers.push_back(std::thread(resolve, left_splited[2] - left_splited[0], rigth_splited[0] + rigth_splited[1], std::ref(P6)));
    multipliers.push_back(std::thread(resolve, left_splited[1] - left_splited[3], rigth_splited[2] + rigth_splited[3], std::ref(P7)));
    for (int i = 0; i < multipliers.size(); i++) {
        multipliers[i].join();
    }
    Matrix C11 = P1 + P4 - P5 + P7;
    Matrix C12 = P3 + P5;
    Matrix C21 = P2 + P4;
    Matrix C22 = P1 - P2 + P3 + P6;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            result.matrix[i][j] = C11.matrix[i][j];
            result.matrix[i][dimension + j] = C12.matrix[i][j];
            result.matrix[dimension + i][j] = C21.matrix[i][j];
            result.matrix[dimension + i][dimension + j] = C22.matrix[i][j];
        }
    }
}

void resolve(
    Matrix left,
    Matrix right,
    Matrix &result
) {
    int dimension = result.matrix.size() / 2;
    if (dimension == 8) {
        result = left * right;
        return;
    }
    Matrix P1 = Matrix::empty_matrix(dimension);
    Matrix P2 = Matrix::empty_matrix(dimension);
    Matrix P3 = Matrix::empty_matrix(dimension);
    Matrix P4 = Matrix::empty_matrix(dimension);
    Matrix P5 = Matrix::empty_matrix(dimension);
    Matrix P6 = Matrix::empty_matrix(dimension);
    Matrix P7 = Matrix::empty_matrix(dimension);
    std::vector<Matrix> left_splited = split(left);
    std::vector<Matrix> rigth_splited = split(right);
    resolve(left_splited[0] + left_splited[3], rigth_splited[0] + rigth_splited[3], P1);
    resolve(left_splited[2] + left_splited[3], rigth_splited[0], P2);
    resolve(left_splited[0], rigth_splited[1] - rigth_splited[3], P3);
    resolve(left_splited[3], rigth_splited[2] - rigth_splited[0], P4);
    resolve(left_splited[0] + left_splited[1], rigth_splited[3], P5);
    resolve(left_splited[2] - left_splited[0], rigth_splited[0] + rigth_splited[1], P6);
    resolve(left_splited[1] - left_splited[3], rigth_splited[2] + rigth_splited[3], P7);
    Matrix C11 = P1 + P4 - P5 + P7;
    Matrix C12 = P3 + P5;
    Matrix C21 = P2 + P4;
    Matrix C22 = P1 - P2 + P3 + P6;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            result.matrix[i][j] = C11.matrix[i][j];
            result.matrix[i][dimension + j] = C12.matrix[i][j];
            result.matrix[dimension + i][j] = C21.matrix[i][j];
            result.matrix[dimension + i][dimension + j] = C22.matrix[i][j];
        }
    }
}

std::vector<Matrix> split(Matrix matrix) {
    int dimension = matrix.matrix.size() / 2;
    Matrix A = Matrix::empty_matrix(dimension);
    Matrix B = Matrix::empty_matrix(dimension);
    Matrix C = Matrix::empty_matrix(dimension);
    Matrix D = Matrix::empty_matrix(dimension);
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            A.matrix[i][j] = matrix.matrix[i][j];
            B.matrix[i][j] = matrix.matrix[i][dimension + j];
            C.matrix[i][j] = matrix.matrix[dimension + i][j];
            D.matrix[i][j] = matrix.matrix[dimension + i][dimension + j];
        }
    }
    return std::vector<Matrix>{A, B, C, D};
}