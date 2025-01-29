#include "tasks_generator.hpp"

std::vector<std::pair<Matrix, Matrix>> generate_tasks(int amount, int size) {
    srand(time(NULL));
    std::vector<std::pair<Matrix, Matrix>> tasks;
    for (int i = 0; i < amount; i++) {
        tasks.push_back(std::make_pair(Matrix(size), Matrix(size)));
    }
    return tasks;
}