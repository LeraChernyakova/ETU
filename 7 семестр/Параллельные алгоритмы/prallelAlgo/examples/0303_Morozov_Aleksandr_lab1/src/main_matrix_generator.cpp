#include "matrix_generator/matrix_generator.hpp"

int main() {

    int first_height = 10;
    int first_width = 10;
    int second_height = 10;
    int second_width = 10;

    generate_multipliers(
        first_height,
        first_width,
        second_height,
        second_width
    );

    return 0;
}