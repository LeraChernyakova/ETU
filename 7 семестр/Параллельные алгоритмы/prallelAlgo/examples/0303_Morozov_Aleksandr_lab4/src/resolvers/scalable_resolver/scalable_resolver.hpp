#include <thread>
#include "../../matrix/matrix.hpp"

void scalable_resolve(
    Matrix left,
    Matrix right,
    Matrix& result,
    int threads
);

void resolve(
    Matrix left,
    Matrix right,
    Matrix& result,
    int threads,
    int index
);