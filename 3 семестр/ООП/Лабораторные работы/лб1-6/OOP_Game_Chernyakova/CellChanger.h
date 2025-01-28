#pragma once

#include "FieldScheme.h"
#include "Concepts.h"
#include "Random.h"

template<CellType Type, TRandom Random = Random<100>>
class CellChanger {
public:
    bool operator()(CellType& type) {
        if (type == CellType::Default && random()) {
            type = Type;
            return true;
        }
        return false;
    }
private:
    Random random;
};