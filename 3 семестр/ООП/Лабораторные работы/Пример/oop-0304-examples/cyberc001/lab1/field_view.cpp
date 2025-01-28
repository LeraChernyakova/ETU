#include "field_view.h"
#include "cells/cell_view.h"

#include <iostream>

field_view::field_view(const field& viewf) : viewf(viewf)
{}

void field_view::display()
{
	for(size_t x = 0; x < viewf.get_w(); ++x)
	{
		for(size_t y = 0; y < viewf.get_h(); ++y)
			std::cout << viewf.get_cell(x, y).get_view().get_disp_char();
		std::cout << '\n';
	}
}
