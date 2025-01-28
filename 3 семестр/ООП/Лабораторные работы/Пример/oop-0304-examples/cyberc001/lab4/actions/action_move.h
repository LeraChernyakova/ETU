#ifndef ACTION_MOVE_H
#define ACTION_MOVE_H

#include "action.h"

#include <cstddef>

class action_move : public action
{
	public:

	action_move(double ap_per_cell);

	size_t getAPCost(actor* active, actor* passive, cell* c);
	bool canExecute(size_t ap, actor* active, actor* passive, cell* c);

	void execute(size_t& ap, actor* active, actor* passive, cell* c);

	protected:

	double ap_per_cell;
};

#endif
