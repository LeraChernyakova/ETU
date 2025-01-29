#include "result_writer.hpp"

void write_result(std::vector<std::vector<int>> result_matrix) {
    std::ofstream out;
    out.open("./data/result.txt");
    if (out.is_open())
    {
        int height = result_matrix.size();
        int width = result_matrix[0].size();
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width - 1; j++) {
                out << result_matrix[i][j] << " ";
            }
            out << result_matrix[i][width - 1] << std::endl;
        }
    }
    out.close();
}