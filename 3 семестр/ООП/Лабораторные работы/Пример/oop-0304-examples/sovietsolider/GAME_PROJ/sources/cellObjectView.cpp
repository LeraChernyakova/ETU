#include "../headers/cellObjectView.h"

CellObjectView::CellObjectView(char disp_char, CellObject& owner): disp_char(disp_char), owner(owner)
{}

char CellObjectView::get_disp_char() const
{
	return disp_char;
}