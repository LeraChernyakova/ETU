#include "CellView.h"
#include <typeinfo>

void CellView::printCell(Cell cell) {
    if (cell.getActive()) {
        std::cout << "|P|";
    }
    else {
        if (cell.getBarrier())
            std::cout << "|R|";
        else {
            if (!(cell.getEvent()))
                std::cout << "| |";
            if (dynamic_cast<Cave *>(cell.getEvent()))
                std::cout << "|C|";
            if (dynamic_cast<Clan *>(cell.getEvent()))
                std::cout << "|!|";
            if (dynamic_cast<Exit *>(cell.getEvent()))
                std::cout << "|E|";
            if (dynamic_cast<Hungry *>(cell.getEvent()))
                std::cout << "|H|";
            if (dynamic_cast<Resource *>(cell.getEvent()))
                std::cout << "|*|";
        }
    }
}