#ifndef ACTION_COMBAT_H
#define ACTION_COMBAT_H

#include "action.h"

#include <cstddef>

class action_combat : public action
{
	public:

	action_combat(size_t dmg);

	virtual size_t getDamageAmount(actor* active, actor* passive, cell* c);

	virtual bool canExecute(size_t ap_amt, actor* active, actor* passive, cell* c);
	void execute(size_t& ap_amt, actor* active, actor* passive, cell* c);

	protected:

	size_t dmg;
};

#endif
