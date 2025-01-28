#include "cell_exit.h"
#include "cell_view.h"

cell_exit::cell_exit(field* parf, size_t x, size_t y, bool passable) : cell(parf, x, y, passable) {}

void cell_exit::init_view()
{
	cv = new cell_view(']', *this);
}
