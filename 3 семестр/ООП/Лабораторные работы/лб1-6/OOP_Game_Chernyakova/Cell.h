#pragma once

#include "IEvent.h"
//#include "FieldFacade.h"

class Cell {
public:
    Cell();
    Cell(const Cell& obj) noexcept;
    Cell& operator=(const Cell& copy) noexcept;
    Cell(Cell&& obj) noexcept;
    Cell& operator=(Cell&& copy) noexcept;
    Cell(bool patency, IEvent* fact);
    void setPatency(bool value);
    bool getPatency() const;
    IEvent* getFact() const;
    void changeFact(IEvent* new_fact);
    void react() const;
    bool getActive() const;
    void setActive(bool active);
    ~Cell();

private:
    bool patency;//можно ли ступить на клетку
    mutable IEvent* fact;//событие
    bool active;

};