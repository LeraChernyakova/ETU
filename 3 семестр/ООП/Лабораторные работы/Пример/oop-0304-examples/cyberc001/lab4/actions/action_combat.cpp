#include "action_combat.h"

#include <sstream>
#include <string>
#include "../logger/global_logger.h"

action_combat::action_combat(size_t dmg) : dmg(dmg) {}

size_t action_combat::getDamageAmount(actor* active, actor* passive, cell* c) { return dmg; }
bool action_combat::canExecute(size_t ap, actor* active, actor* passive, cell* c)
{
	if(ap < getAPCost(active, passive, c))
		return false;
	if(passive == nullptr)
		return false;
	return true;
}

void action_combat::execute(size_t& ap, actor* active, actor* passive, cell* c)
{
	size_t dmgdealt = passive->takeDamage(dmg);
	ap -= getAPCost(active, passive, c);

	std::stringstream ss;
	ss << active->getName() << " dealt " << dmgdealt << " damage to " << passive->getName();
	global_logger::message(ss.str());
}
