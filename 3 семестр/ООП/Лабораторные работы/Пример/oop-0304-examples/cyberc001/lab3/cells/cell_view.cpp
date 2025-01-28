#include "cell_view.h"

#include "../cell_object_view.h"

cell_view::cell_view(char disp_char, cell& owner) : disp_char(disp_char), owner(owner)
{}


char cell_view::get_disp_char() const
{
	if(owner.has_object())
		return owner.get_object().getView().get_disp_char();
	return disp_char;
}
