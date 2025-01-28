#include "action_combat.h"

#include <sstream>
#include <string>
#include "../logger/global_logger.h"

#include "../save/class_creator_inserter.h"

action_combat::action_combat(size_t base_dmg) : base_dmg(base_dmg) {}

size_t action_combat::getDamageAmount(actor* active, actor* passive, cell* c) { return base_dmg; }

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
	size_t dmgdealt = passive->takeDamage(base_dmg);
	ap -= getAPCost(active, passive, c);

	std::stringstream ss;
	ss << active->getName() << " dealt " << dmgdealt << " damage to " << passive->getName();
	global_logger::message(GLOGGER_LEVEL_EVENT, ss.str());
}

void action_combat::saveToFile(savestream& svs)
{
	action::saveToFile(svs);
	svs.writeBytes(&base_dmg, sizeof(base_dmg));
}
void action_combat::loadFromFile(savestream& svs)
{
	action::loadFromFile(svs);
	svs.readBytes(&base_dmg, sizeof(base_dmg));
}
