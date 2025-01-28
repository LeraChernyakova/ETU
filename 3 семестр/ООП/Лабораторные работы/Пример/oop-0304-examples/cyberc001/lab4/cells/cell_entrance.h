#ifndef CELL_ENTRANCE_H
#define CELL_ENTRANCE_H

#include "cell.h"

class cell_entrance : public cell
{
	public:

	cell_entrance(field* parf, size_t x, size_t y, bool passable);

	protected:

	void init_view();
};

#endif
