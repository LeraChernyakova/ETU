#include "FieldRegister.h"
#include "CellRegister.h"

FieldScheme FieldRegister::getScheme(const Field& field) {
    std::vector<std::vector<CellType>> map;
    map.resize(field.getHeight());
    for (int i = 0; i < field.getHeight(); i++) {
        map[i].resize(field.getWidth());
    }
    for (int i = 0; i < field.getHeight(); i++) {
        auto* cells = field[i];
        for (int j = 0; j < field.getWidth(); j++) {
            map[i][j] = CellRegister::getCellType(cells[j]);
        }
    }
    FieldScheme scheme{ map, field.getHeight(), field.getWidth() };
    return scheme;
}