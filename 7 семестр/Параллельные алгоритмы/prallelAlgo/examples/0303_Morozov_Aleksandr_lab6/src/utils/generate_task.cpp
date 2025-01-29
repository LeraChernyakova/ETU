#include "../include/utils.hpp"


std::pair<std::vector<int>, std::vector<int>> generate_task(int size) {
    srand(time(NULL));
    std::vector<int> left(size * size);
    std::vector<int> right(size * size);
    for (int i = 0; i < size * size; i++) {
        left[i] = -10 + rand() % 21;
    }
    for (int i = 0; i < size * size; i++) {
        right[i] = -10 + rand() % 21;
    }
    return std::make_pair(left, right);
}