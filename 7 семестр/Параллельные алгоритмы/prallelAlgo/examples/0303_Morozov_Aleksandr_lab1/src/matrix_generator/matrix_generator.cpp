#include "matrix_generator.hpp"

void generate_first_multiplier(int height, int width) {
    std::vector<std::vector<int>> matrix = generate_matrix_body(height, width);
    std::ofstream out;
    out.open("./data/first_multiplier.txt");
    if (out.is_open())
    {
        out << height << " " << width << std::endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width - 1; j++) {
                out << matrix[i][j] << " ";
            }
            out << matrix[i][width - 1] << std::endl;
        }
    }
    out.close(); 
}

void generate_second_multiplier(int height, int width) {
    std::vector<std::vector<int>> matrix = generate_matrix_body(height, width);
    std::ofstream out;
    out.open("./data/second_multiplier.txt");
    if (out.is_open())
    {
        out << height << " " << width << std::endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width - 1; j++) {
                out << matrix[i][j] << " ";
            }
            out << matrix[i][width - 1] << std::endl;
        }
    }
    out.close();
}

std::vector<std::vector<int>> generate_matrix_body(int height, int width) {
    std::vector<std::vector<int>> matrix(height, std::vector<int>(width));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            matrix[i][j] = -10 + rand() % 21;
        }
    }
    return matrix;
}

void generate_multipliers(int first_height, int first_width,
                          int second_height, int second_width
) {
    srand(time(NULL));
    generate_first_multiplier(first_height, first_width);
    generate_second_multiplier(second_height, second_width);
}