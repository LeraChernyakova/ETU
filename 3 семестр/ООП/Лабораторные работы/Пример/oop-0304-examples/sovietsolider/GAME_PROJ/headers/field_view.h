#ifndef FIELDVIEW_H
#define FIELDVIEW_H
#include "field.h"

class FieldView
{
private:
    Field& view;

public:
    FieldView(Field& _view);
    void display();
};

#endif // FIELDVIEW_H
