#include "CellView.h"

CellView::CellView(Cell& cell) {
    if (cell.is_wall()) {
        cell_view = '#';
        return;
    }
    if (dynamic_cast<CoinEvent*>(cell.get_event()) != nullptr) {
        cell_view = 'C';
    }
    else if (dynamic_cast<Buff*>(cell.get_event()) != nullptr) {
        cell_view = 'B';
    }
    else if (dynamic_cast<PoisonTrap*>(cell.get_event()) != nullptr || dynamic_cast<FrozenTrap*>(cell.get_event()) != nullptr) {
        cell_view = 'T';
    }
    else if (dynamic_cast<HealEvent*>(cell.get_event()) != nullptr) {
        cell_view = 'H';
    }
    else if (dynamic_cast<FieldNoWalls*>(cell.get_event()) != nullptr) {
        cell_view = 'N';
    }
    else if (dynamic_cast<TreasureEvent*>(cell.get_event()) != nullptr) {
        cell_view = 'W';
    }
    else {
        cell_view = ' ';
    }
}

char CellView::get_view() const {
    return this->cell_view;
};