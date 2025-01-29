#include <thread>
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
    std::vector<std::vector<int>> &result_matrix
) {
    int height = first_multiplier.size();
    int width = second_multiplier[0].size();
    int equal_line = second_multiplier.size();
    std::vector<std::vector<int>> tmp_matrix(height, std::vector<int>(width));
    int tmp_sum;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            tmp_sum = 0;
            for (int n = 0; n < equal_line; n++) {
                tmp_sum += (first_multiplier[i][n] * second_multiplier[n][j]);
            }
            tmp_matrix[i][j] = tmp_sum;
        }
    }
    result_matrix = tmp_matrix;
}

void write_task(std::vector<std::vector<int>> result_matrix) {
    write_result(result_matrix);
}


int main() {
    std::vector<std::vector<int>> first_multiplier;
    std::vector<std::vector<int>> second_multiplier;
    std::vector<std::vector<int>> result_matrix;

    std::thread reader(
        read_task,
        std::ref(first_multiplier),
        std::ref(second_multiplier)
    );
    reader.join();

    std::thread multiplicator(
        multiplication_task,
        first_multiplier,
        second_multiplier,
        std::ref(result_matrix)
    );
    multiplicator.join();

    std::thread writer(write_task, result_matrix);
    writer.join();

    return 0;
}