#include "scalable_resolver.hpp"

void scalable_resolve(
    Matrix left,
    Matrix right,
    Matrix& result,
    int threads
) {
    std::vector<std::thread> multipliers;
    for (int i = 0; i < threads; i++) {
        multipliers.push_back(
            std::thread(resolve, left, right, std::ref(result), threads, i)
        );
    }
    for (int i = 0; i < threads; i++) {
        multipliers[i].join();
    }
}

void resolve(
    Matrix left,
    Matrix right,
    Matrix& result,
    int threads,
    int index
) {
    for (int order = index; order < result.elements; order += threads) {
        int dimension = result.matrix.size();
        int i = order / dimension;
        int j = order % dimension;
        int sum = 0;
        for (int m = 0; m < dimension; m++) {
            sum += (left.matrix[i][m] * right.matrix[m][j]);
        }
        result.matrix[i][j] = sum;
    }
}