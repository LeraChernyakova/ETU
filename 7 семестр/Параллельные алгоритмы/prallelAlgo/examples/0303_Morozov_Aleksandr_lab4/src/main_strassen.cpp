#include "./resolvers/strassen_resolver/strassen_resolver.hpp"
#include "./tasks_generator/tasks_generator.hpp"
#include <iostream>
#include <chrono>


int main() {

    int matrix_size = 32;
    int tasks_amount = 1;

    std::ofstream out;
    out.open("./data/strassen_result.txt");
    if (!out.is_open()) exit(-1);

    std::vector<std::pair<Matrix, Matrix>> tasks = generate_tasks(tasks_amount, matrix_size);
    std::vector<Matrix> results;

    auto start_programm = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < tasks_amount; i++) {
        Matrix result = Matrix::empty_matrix(matrix_size);
        strassen_resolve(tasks[i].first, tasks[i].second, result);
        results.push_back(result);
    }

    auto end_programm = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_programm - start_programm);
    std::cout << duration.count() << std::endl;

    for (int i = 0; i < results.size(); i++) {
        out << results[i];
    }

    out.close();

    return 0;
}