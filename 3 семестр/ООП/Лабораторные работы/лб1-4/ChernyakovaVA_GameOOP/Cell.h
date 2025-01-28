#pragma once

#include "Event.h"
#include <algorithm>

class Cell {
private:
    bool wall;
    Event* event;
public:
    explicit Cell(bool wall = false, Event* ev = nullptr) : wall(wall), event(ev) {};
    Cell(const Cell& other);
    Cell(Cell&& other) noexcept;
    Cell& operator=(const Cell& other);
    ~Cell();
    void swap(Cell& other);
    void set_event(Event* ev);
    void set_wall(bool value);
    bool is_wall() const;
    Event* get_event();
};