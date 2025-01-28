#pragma once

#include <string>
#include <vector>

class CellRegister;
enum class CellType {
    Default,
    Player,
    Wall,
    Bomb,
    Water,
    Teleport,
    MapChange,
    Key,
    Door,
    Undefined
};

struct FieldScheme {
    std::vector<std::vector<CellType>> array;
    int height;
    int width;
    explicit operator std::string() const;
};