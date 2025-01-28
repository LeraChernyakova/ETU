#ifndef ACTION_SHOOT_BALLISTIC_H
#define ACTION_SHOOT_BALLISTIC_H

#include "action_combat.h"

class action_shoot_ballistic : public action_combat
{
	public:

	action_shoot_ballistic(size_t dmg, size_t ap_cost, size_t range);

	virtual size_t getAPCost(actor* active, actor* passive, cell* c);
	virtual bool canExecute(size_t ap_amt, actor* active, actor* passive, cell* c);


	protected:

	size_t ap_cost;
	size_t range;
};

#endif
