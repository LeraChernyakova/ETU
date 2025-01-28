#pragma once

#include "Concepts.h"
#include "FieldScheme.h"
#include <ctime>
template<int Count, TCellChanger CellChanger>
class RandomGenerator {
public:
    RandomGenerator() {
        std::srand(time(nullptr));
    }

    void operator()(FieldScheme& scheme) {
        int count = Count;
        while (count != 0) {
            if (cell_changer(scheme.array[std::rand() % scheme.height][std::rand() % scheme.width]))
                --count;
        }
    }
private:
    CellChanger cell_changer;
};