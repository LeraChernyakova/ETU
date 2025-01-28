#ifndef CELL_OBJECT_VIEW_H
#define CELL_OBJECT_VIEW_H

#include "cell_object.h"

class cell_object_view
{
	public:

	cell_object_view(char disp_char, cell_object& owner);

	char get_disp_char() const;


	private:

	char disp_char;
	cell_object& owner;
};

#endif
