#ifndef CELL_VIEW_H
#define CELL_VIEW_H

#include "cell.h"

class cell_view
{
	public:

	cell_view(char disp_char, cell& owner);

	char get_disp_char() const;


	private:

	char disp_char;
	cell& owner;
};

#endif
