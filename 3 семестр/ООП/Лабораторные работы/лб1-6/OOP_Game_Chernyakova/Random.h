#pragma once

#include <ctime>
#include <cstdlib>

template<int P>
class Random {
public:
    Random() {
        std::srand(time(nullptr));
    }
    bool operator()() {
        int t = std::rand() % 100;
        return t < P;
    }
};