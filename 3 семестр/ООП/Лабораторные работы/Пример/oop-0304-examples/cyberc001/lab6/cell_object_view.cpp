#include "cell_object_view.h"

cell_object_view::cell_object_view(char disp_char, cell_object& owner): disp_char(disp_char), owner(owner)
{}

char cell_object_view::get_disp_char() const
{
	return disp_char;
}
