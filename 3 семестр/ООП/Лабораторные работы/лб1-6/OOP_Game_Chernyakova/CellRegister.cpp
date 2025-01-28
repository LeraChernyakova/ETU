#include "CellRegister.h"
#include "Water.h"
#include "Bomb.h"
#include "DoorEvent.h"
#include "KeyEvent.h"
#include "MapChange.h"
#include "Teleport.h"

char CellRegister::getSymb(const Cell& cell) {
    if (cell.getActive()) {
        return 'P';
    }
    if (!cell.getPatency()) {
        return '#';
    }
    if (!cell.getFact()) {
        return '.';
    }

    auto type = map[typeid(*cell.getFact()).hash_code()];
    return cell_map[type];
}
std::unordered_map<CellType, char> CellRegister::cell_map{
    {CellType::Default, '.'}, {CellType::Player, 'P'},
    {CellType::Wall, '#'}, {CellType::Bomb, 'B'},
    {CellType::Water, 'W'}, {CellType::MapChange, 'M'},
    {CellType::Teleport, 'T'}, {CellType::Key, 'K'},
    {CellType::Door, 'D'}, {CellType::Undefined, '?'}
};

std::unordered_map<std::size_t, CellType> CellRegister::map{
    {typeid(Water).hash_code(), CellType::Water},
    {typeid(Bomb).hash_code(), CellType::Bomb},
    {typeid(DoorEvent).hash_code(), CellType::Door},
    {typeid(KeyEvent).hash_code(), CellType::Key},
    {typeid(MapChange).hash_code(), CellType::MapChange},
    {typeid(Teleport).hash_code(), CellType::Teleport}
};
char CellRegister::getSymb(CellType cell) {
    switch (cell) {
    case CellType::Default:return '.';
    case CellType::Player:return 'P';
    case CellType::Wall:return '#';
    case CellType::Bomb:return 'B';
    case CellType::Water:return 'W';
    case CellType::Teleport:return 'T';
    case CellType::MapChange:return 'M';
    case CellType::Key:return 'K';
    case CellType::Door:return 'D';
    case CellType::Undefined:return '?';
    }
}
CellType CellRegister::getType(char symb) {
    CellType type = CellType::Undefined;
    std::any_of(cell_map.cbegin(), cell_map.cend(), [symb, &type](auto&& pair) -> bool {
        if (pair.second == symb) {
            type = pair.first;
            return true;
        }
        return false;
        });
    return type;
}
CellType CellRegister::getCellType(const Cell& cell) {
    if (cell.getActive()) {
        return CellType::Player;
    }
    if (!cell.getPatency()) {
        return CellType::Wall;
    }
    if (!cell.getFact()) {
        return CellType::Default;
    }

    auto type = map[typeid(*cell.getFact()).hash_code()];
    return type;
}