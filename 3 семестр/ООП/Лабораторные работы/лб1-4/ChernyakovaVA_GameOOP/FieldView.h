#pragma once

#include "Field.h"
#include "CellView.h"
#include "Game.h"
#include "IObserver.h"
#include <iostream>

class FieldView : public IObserver {
private:
    void write_field() const;
    Field* field;
public:
    FieldView() = default;
    explicit FieldView(Field* map);
    ~FieldView() = default;
    void update() override;
};