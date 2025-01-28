#ifndef FIELD_VIEW_H
#define FIELD_VIEW_H

#include "field.h"

class field_view
{
	public:

	field_view(const field& viewf);

	void display();
	void setHighlight(bool do_highlight, size_t x = 0, size_t y = 0);


	private:

	const field& viewf;
	bool do_hl = false; size_t hl_x, hl_y;
};

#endif
