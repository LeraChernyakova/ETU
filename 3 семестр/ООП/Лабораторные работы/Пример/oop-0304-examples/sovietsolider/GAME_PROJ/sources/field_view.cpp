#include "../headers/field_view.h"

FieldView::FieldView(Field& _view) : view(_view)
{}

void FieldView::display()
{
    
    for(int i=0; i<view.get_size_y(); i++)
    {
        std::cout << std::endl;
        for(int j=0; j<view.get_size_x(); j++)
            std::cout << view.get_cell(j,i).get_display().get_disp_char();
    }
    std::cout << '\n';
}
