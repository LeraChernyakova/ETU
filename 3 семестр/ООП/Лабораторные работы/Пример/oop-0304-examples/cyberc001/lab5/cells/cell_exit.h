#ifndef CELL_EXIT_H
#define CELL_EXIT_H

#include "cell.h"

class cell_exit : public cell
{
	public:

	cell_exit(field* parf, size_t x, size_t y, bool passable);

	protected:

	void init_view();
};

#endif
