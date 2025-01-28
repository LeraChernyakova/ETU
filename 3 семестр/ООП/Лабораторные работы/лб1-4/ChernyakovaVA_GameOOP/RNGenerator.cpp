#include "RNGenerator.h"

RNGenerator::RNGenerator() {
    std::random_device dev;
    this->seed = dev();
    std::mt19937 gen(seed);
    this->rang_gen = gen;
}

RNGenerator::RNGenerator(int64_t s) : seed(s), rang_gen(s) {
}

int64_t RNGenerator::get_seed() const {
    return seed;
}