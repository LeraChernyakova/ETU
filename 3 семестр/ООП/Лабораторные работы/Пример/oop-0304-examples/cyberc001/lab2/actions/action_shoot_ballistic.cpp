#include "action_shoot_ballistic.h"

action_shoot_ballistic::action_shoot_ballistic(size_t dmg, size_t ap_cost, size_t range) : action_combat(dmg)
{
	this->ap_cost = ap_cost;
	this->range = range;
}

bool action_shoot_ballistic::canExecute(size_t ap_amt, actor* active, actor* passive, cell* c)
{
	if(!action_combat::canExecute(ap_amt, active, passive, c))
		return false;

	if(active->getParentCell().get_distance(*c) > range)
		return false;

	return true;
}
size_t action_shoot_ballistic::getAPCost(actor* active, actor* passive, cell* c) { return ap_cost; }
