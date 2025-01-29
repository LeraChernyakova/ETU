#include <thread>
#include "../../matrix/matrix.hpp"


void strassen_resolve(
    Matrix left,
    Matrix right,
    Matrix &result
);

void resolve(
    Matrix left,
    Matrix right,
    Matrix &result
);

std::vector<Matrix> split(Matrix matrix);