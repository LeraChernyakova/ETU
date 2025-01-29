#include <thread>
#include <cmath>
#include <chrono>
#include <iostream>
#include "matrix_reader/matrix_reader.hpp"
#include "result_writer/result_writer.hpp"

void read_task(
    std::vector<std::vector<int>> &first_multiplier,
    std::vector<std::vector<int>> &second_multiplier
) {
    first_multiplier = read_first_multiplier();
    second_multiplier = read_second_multiplier();
}

void multiplication_task(
    std::vector<std::vector<int>> first_multiplier,
    std::vector<std::vector<int>> second_multiplier,
    int start,
    int elem_amount,
    std::vector<std::vector<int>> &result_matrix
) {
    int height = first_multiplier.size();
    int width = second_multiplier[0].size();
    int equal_line = second_multiplier.size();
    int tmp_sum, i, j;
    for (int l = start; l < start + elem_amount; l++) {
        tmp_sum = 0;
        i = l / width;
        j = l - i * width;
        for (int n = 0; n < equal_line; n++) {
            tmp_sum += (first_multiplier[i][n] * second_multiplier[n][j]);
        }
        result_matrix[i][j] = tmp_sum;
    }
}

void write_task(std::vector<std::vector<int>> result_matrix) {
    write_result(result_matrix);
}


int main() {

    auto start_programm = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<int>> first_multiplier;
    std::vector<std::vector<int>> second_multiplier;

    std::thread reader(
        read_task,
        std::ref(first_multiplier),
        std::ref(second_multiplier)
    );
    reader.join();

    int thread_amount = 4;
    int height = first_multiplier.size();
    int width = second_multiplier[0].size();
    std::vector<std::vector<int>> result_matrix(height, std::vector<int>(width));
    int elem_amount = height * width;
    int elem_per_thread = ceil((double)elem_amount / thread_amount);
    int last_thread_elem = elem_amount - (thread_amount - 1) * elem_per_thread;
    std::vector<std::thread> threads;
    int tmp_start = 0;
    for (int i = 0; i < thread_amount - 1; i++) {
        threads.push_back(std::thread(
            multiplication_task,
            first_multiplier,
            second_multiplier,
            tmp_start,
            elem_per_thread,
            std::ref(result_matrix)
        ));
        tmp_start += elem_per_thread;
    }
    threads.push_back(std::thread(
        multiplication_task,
        first_multiplier,
        second_multiplier,
        tmp_start,
        last_thread_elem,
        std::ref(result_matrix)
    ));
    for (int i = 0; i < threads.size(); i++) {
        threads[i].join();
    }

    std::thread writer(write_task, result_matrix);
    writer.join();

    auto end_programm = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_programm - start_programm);
    std::cout << duration.count() << std::endl;

    return 0;
}