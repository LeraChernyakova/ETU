#ifndef CELL_ENTRANCE_H
#define CELL_ENTRANCE_H

#include "cell.h"

class cell_entrance : public cell
{
	public:

	cell_entrance(field* parf = nullptr, size_t x = 0, size_t y = 0, bool passable = true);

	// serialization
	virtual std::string getClassName();


	protected:

	void init_view();
};

#endif
