#include "cell_view.h"

cell_view::cell_view(char disp_char) : disp_char(disp_char)
{}


char cell_view::get_disp_char() const
{
	return disp_char;
}
