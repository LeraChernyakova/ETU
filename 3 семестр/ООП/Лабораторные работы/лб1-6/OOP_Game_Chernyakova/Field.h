#pragma once

#include "Cell.h"
#include "IFieldObserver.h"

class Field {
public:
    Field();
    Field(int width, int height);
    Field(int width, int height, Cell** array);
    Field(const Field& obj) noexcept;
    Field& operator=(const Field& copy) noexcept;
    Field(Field&& copy) noexcept;
    Field& operator=(Field&& copy) noexcept;
    int getWidth() const;
    int getHeight() const;
    const Cell& getCell(int x, int y);
    const Cell* operator[](int row) const;
    bool isPointPassable(int x, int y);
    void setCellPatency(int x, int y, bool value);
    void setCellEvent(int x, int y, IEvent* event);
    void setCellActive(int x, int y, bool value);
    void setObserver(IFieldObserver* obs);
    IEvent* getCellEvent(int x, int y);
    ~Field();

private:
    int width;
    int height;
    Cell** array;
    IFieldObserver* observer;

};