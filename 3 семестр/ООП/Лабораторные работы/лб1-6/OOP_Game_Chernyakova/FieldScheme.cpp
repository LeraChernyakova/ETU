#include "FieldScheme.h"
#include "CellRegister.h"

FieldScheme::operator std::string() const {
    std::string out;
    out.reserve((width + 1) * height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            out += CellRegister::getSymb(array[i][j]);
        }
        out += "\n";
    }
    return out;
}