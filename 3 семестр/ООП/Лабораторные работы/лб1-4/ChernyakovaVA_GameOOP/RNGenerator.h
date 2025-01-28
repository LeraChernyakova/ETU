#pragma once

#include <random>

class RNGenerator {
public:
    RNGenerator();
    RNGenerator(int64_t s);
    int64_t get_seed() const;//целочисленный тип фиксированной ширины

    template<typename R, typename I>
    R get_random_value(I& distr) {
        return distr(rang_gen);
    }

    ~RNGenerator() = default;
private:
    std::mt19937 rang_gen;//генератор
    int64_t seed;
};
