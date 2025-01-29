#include <vector>
#include <fstream>

void generate_multipliers(
    int first_height,
    int first_width,
    int second_height,
    int second_width
);
void generate_first_multiplier(int height, int width);
void generate_second_multiplier(int height, int width);
std::vector<std::vector<int>> generate_matrix_body(int height, int width);