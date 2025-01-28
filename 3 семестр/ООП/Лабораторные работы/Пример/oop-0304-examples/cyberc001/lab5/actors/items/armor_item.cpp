#include "armor_item.h"

#include <sstream>
#include <string>
#include "../../logger/global_logger.h"

armor_item::armor_item(size_t dt, double dr)
{
	actions.push_back(new armor_item_wear(*this, dt, dr));
}

const char* armor_item::getName() const { return "Armor"; }

bool armor_item::isWorn() const { return worn; }
void armor_item::setWorn(bool _worn) { worn = _worn; }

// wear action

armor_item_wear::armor_item_wear(armor_item& item, size_t dt, double dr)
	: item(item), dt(dt), dr(dr) {}

const std::string armor_item_wear::getName()
{
	if(item.isWorn())
		return "take off";
	return "put on";
}

size_t armor_item_wear::getAPCost(actor* active, actor* passive, cell* c)
{
	return 3;
}
bool armor_item_wear::canExecute(size_t ap, actor* active, actor* passive, cell* c)
{
	if(ap < getAPCost(active, passive, c))
		return false;
	if(!active)
		return false;

	return true;
}
void armor_item_wear::execute(size_t& ap, actor* active, actor* passive, cell* c)
{
	if(item.isWorn()){
		active->setDamageThreshold(active->getDamageThreshold() - dt);
		active->setDamageResistance(active->getDamageResistance() - dr);
	}
	else{
		active->setDamageThreshold(active->getDamageThreshold() + dt);
		active->setDamageResistance(active->getDamageResistance() + dr);
	}

	std::stringstream ss;
	if(item.isWorn())
		ss << active->getName() << " took off \"" << item.getName() << "\"";
	else
		ss << active->getName() << " put on \"" << item.getName() << "\"";
	global_logger::message(GLOGGER_LEVEL_EVENT, ss.str());

	item.setWorn(!item.isWorn());
	ap -= getAPCost(active, passive, c);
}
