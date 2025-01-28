#include "action_shoot_ballistic.h"

#include "../save/class_creator_inserter.h"

action_shoot_ballistic::action_shoot_ballistic(size_t dmg, size_t ap_cost, size_t range) : action_combat(dmg)
{
	this->ap_cost = ap_cost;
	this->range = range;
}

const std::string action_shoot_ballistic::getName()
{
	return "shoot a ballistic projectile";
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

static default_constructor_func dcf = [](){ return new action_shoot_ballistic(); };
static class_creator_inserter cci("action_shoot_ballistic", &dcf);
std::string action_shoot_ballistic::getClassName(){ return "action_shoot_ballistic"; }
void action_shoot_ballistic::saveToFile(savestream& svs)
{
	action_combat::saveToFile(svs);
	svs.writeBytes(&ap_cost, sizeof(ap_cost));
	svs.writeBytes(&range, sizeof(range));
}
void action_shoot_ballistic::loadFromFile(savestream& svs)
{
	action_combat::loadFromFile(svs);
	svs.readBytes(&ap_cost, sizeof(ap_cost));
	svs.readBytes(&range, sizeof(range));
}
