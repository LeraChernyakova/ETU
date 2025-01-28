#include "cell_entrance.h"
#include "cell_view.h"

cell_entrance::cell_entrance(field* parf, size_t x, size_t y, bool passable) : cell(parf, x, y, passable){}

void cell_entrance::init_view()
{
	cv = new cell_view('[', *this);
}
