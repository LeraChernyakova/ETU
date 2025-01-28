#include "Cell.h"

Cell::Cell() {
    patency = true;
    type = "nothing";//По умолчанию клетка проходима
}
Cell::Cell(bool patency = true, std::string type = "nothing") :patency(patency), type(type) {}
Cell::Cell(const Cell& obj){
    type = obj.type;
    patency = obj.patency;
}

Cell::Cell(const Cell& obj, const Cell& obj2){
    type = obj.type;
}

void Cell::setType(std::string type_) {
    type = type_;
}
std::string Cell::getType() {
    return type;
}

void Cell::setPatency(bool patency_) {
    patency = patency_;
}
bool Cell::getPatency() {
    return patency;
}

bool Cell::isPlayerHere() {
    if (type == "player")
        return true;
    else 
        return false;
}