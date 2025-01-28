#pragma once

class Cell;
class IFieldObserver {
public:
    virtual void onCellEventChanged(int x, int y) = 0;
    virtual void onCellPatencyChanged(int x, int y, bool patency) = 0;
    virtual void onCellActivityChanged(int x, int y, const Cell& cell) = 0;
    //   virtual IFieldObserver& operator<<(const Field& field) = 0;
};