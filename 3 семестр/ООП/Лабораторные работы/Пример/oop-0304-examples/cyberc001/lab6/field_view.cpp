#include "field_view.h"
#include "cells/cell_view.h"

#include <iostream>

field_view::field_view(const field& viewf) : viewf(viewf)
{}

void field_view::display()
{
	static const char* tclr_normal = "\033[0m";
	static const char* tclr_inverse = "\033[7m";

	for(size_t x = 0; x < viewf.get_w(); ++x)
	{
		for(size_t y = 0; y < viewf.get_h(); ++y){
			if(do_hl && x == hl_x && y == hl_y) std::cout << tclr_inverse;
			std::cout << viewf.get_cell(x, y).get_view().get_disp_char();
			if(do_hl && x == hl_x && y == hl_y) std::cout << tclr_normal;
		}
		std::cout << '\n';
	}
}
void field_view::setHighlight(bool do_highlight, size_t x, size_t y)
{
	do_hl = do_highlight;
	hl_x = x; hl_y = y;
}
