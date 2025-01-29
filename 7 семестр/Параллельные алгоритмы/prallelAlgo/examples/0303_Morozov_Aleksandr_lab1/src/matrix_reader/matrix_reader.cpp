#include "matrix_reader.hpp"

std::vector<std::vector<int>> read_first_multiplier() {
    std::vector<std::vector<int>> matrix;
    std::ifstream in("./data/first_multiplier.txt");
    if (in.is_open())
    {
        int height, width;
        in >> height;
        in >> width;
        std::vector<std::vector<int>> tmp(height, std::vector<int>(width));
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                in >> tmp[i][j];
            }
        }
        matrix = tmp;
    }
    in.close();
    return matrix;
}

std::vector<std::vector<int>> read_second_multiplier() {
    std::vector<std::vector<int>> matrix;
    std::ifstream in("./data/second_multiplier.txt");
    if (in.is_open())
    {
        int height, width;
        in >> height;
        in >> width;
        std::vector<std::vector<int>> tmp(height, std::vector<int>(width));
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                in >> tmp[i][j];
            }
        }
        matrix = tmp;
    }
    in.close();
    return matrix;
}