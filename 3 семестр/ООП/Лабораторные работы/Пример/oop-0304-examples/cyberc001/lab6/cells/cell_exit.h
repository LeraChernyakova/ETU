#ifndef CELL_EXIT_H
#define CELL_EXIT_H

#include "cell.h"

class cell_exit : public cell
{
	public:

	cell_exit(field* parf = nullptr, size_t x = 0, size_t y = 0, bool passable = true);

	// serialization
	virtual std::string getClassName();


	protected:

	void init_view();
};

#endif
