#include "./resolvers/scalable_resolver/scalable_resolver.hpp"
#include "./resolvers/strassen_resolver/strassen_resolver.hpp"
#include "./tasks_generator/tasks_generator.hpp"
#include <iostream>


void binary_compare() {
    std::ifstream scablale_in("./data/scalable_result.txt", std::ios::binary);
    std::ifstream straccen_in("./data/strassen_result.txt", std::ios::binary);
    if (!scablale_in.is_open() || !straccen_in.is_open()) exit(-1);
    char scalable_char;
    char strassen_char;
    bool result = true;
    while (scablale_in.get(scalable_char) && straccen_in.get(strassen_char))
    {
        if (scalable_char != scalable_char)
        {
            result = false;
            break;
        }
    }
    if (result) {
        std::cout << "Equal results" << std::endl;
    } else {
        std::cout << "Unequal results" << std::endl;
    }
}


int main() {

    int matrix_size = 64;
    int tasks_amount = 5;
    int threads = 4;

    std::ofstream scalable_out;
    scalable_out.open("./data/scalable_result.txt");
    if (!scalable_out.is_open()) exit(-1);

    std::ofstream strassen_out;
    strassen_out.open("./data/strassen_result.txt");
    if (!strassen_out.is_open()) exit(-1);

    std::vector<std::pair<Matrix, Matrix>> tasks = generate_tasks(tasks_amount, matrix_size);

    for (int i = 0; i < tasks_amount; i++) {
        Matrix result = Matrix::empty_matrix(matrix_size);
        scalable_resolve(tasks[i].first, tasks[i].second, result, threads);
        scalable_out << result;
    }

    for (int i = 0; i < tasks_amount; i++) {
        Matrix result = Matrix::empty_matrix(matrix_size);
        strassen_resolve(tasks[i].first, tasks[i].second, result);
        strassen_out << result;
    }

    scalable_out.close();
    strassen_out.close();

    binary_compare();

    return 0;
}