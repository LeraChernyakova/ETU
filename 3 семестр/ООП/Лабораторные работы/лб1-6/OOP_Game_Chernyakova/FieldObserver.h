#pragma once

#include "IFieldObserver.h"
#include "PrintField.h"
//#include "../Cell/Cell.h"

class FieldObserver : public IFieldObserver {
public:
    void onCellEventChanged(int x, int y) override;
    void onCellPatencyChanged(int x, int y, bool patency) override;
    void onCellActivityChanged(int x, int y, const Cell& cell) override;
    void setPrintField(PrintField* pf);
private:
    PrintField* _pf;
};