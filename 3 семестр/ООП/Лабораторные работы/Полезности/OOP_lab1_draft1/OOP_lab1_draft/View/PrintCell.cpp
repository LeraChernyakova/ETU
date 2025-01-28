#include "PrintCell.h"
#include <typeinfo>

void PrintCell::printCell(Cell cell) {
    if (cell.getActive()) {
        std::cout << "|^_^";
    } else {
        if (cell.getBarrier())
            std::cout << "|###";
        else {
            if (!(cell.getEvent()))
                std::cout << "|   ";
            if (dynamic_cast<Enemy *>(cell.getEvent()))
                std::cout << "|-_-";
            if (dynamic_cast<Money *>(cell.getEvent()))
                std::cout << "| $ ";
            if (dynamic_cast<Food *>(cell.getEvent()))
                std::cout << "| * ";
            if (dynamic_cast<Trap *>(cell.getEvent()))
                std::cout << "|///";
            if (dynamic_cast<Exit *>(cell.getEvent()))
                std::cout << "||E|";
        }
    }
}

PrintCell::PrintCell() = default;
