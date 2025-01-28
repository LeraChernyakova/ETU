#include "armor_item.h"

#include <sstream>
#include <string>
#include "../../logger/global_logger.h"

#include "../../save/class_creator_inserter.h"

armor_item::armor_item(size_t dt, double dr)
{
	actions.push_back(new armor_item_wear(this, dt, dr));
}

const char* armor_item::getName() const { return "Armor"; }

bool armor_item::isWorn() const { return worn; }
void armor_item::setWorn(bool _worn) { worn = _worn; }

// armor item serialization

static default_constructor_func dcf = [](){ return new armor_item(); };
static class_creator_inserter cci("armor_item", &dcf);
std::string armor_item::getClassName(){ return "armor_item"; }
void armor_item::saveToFile(savestream& svs)
{
	item::saveToFile(svs);
	svs.writeBytes(&worn, sizeof(worn));
}
void armor_item::loadFromFile(savestream& svs)
{
	item::loadFromFile(svs);
	svs.readBytes(&worn, sizeof(worn));
	for(auto i = actions.begin(); i != actions.end(); ++i){
		armor_item_wear* aiw = dynamic_cast<armor_item_wear*>(*i);
		if(aiw)
			aiw->setItem(this);
	}
}


// wear action

armor_item_wear::armor_item_wear(armor_item* item, size_t dt, double dr)
	: item(item), dt(dt), dr(dr) {}

void armor_item_wear::setItem(armor_item* item) { this->item = item; }

const std::string armor_item_wear::getName()
{
	if(item->isWorn())
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
	if(item->isWorn()){
		active->setDamageThreshold(active->getDamageThreshold() - dt);
		active->setDamageResistance(active->getDamageResistance() - dr);
	}
	else{
		active->setDamageThreshold(active->getDamageThreshold() + dt);
		active->setDamageResistance(active->getDamageResistance() + dr);
	}

	std::stringstream ss;
	if(item->isWorn())
		ss << active->getName() << " took off \"" << item->getName() << "\"";
	else
		ss << active->getName() << " put on \"" << item->getName() << "\"";
	global_logger::message(GLOGGER_LEVEL_EVENT, ss.str());

	item->setWorn(!item->isWorn());
	ap -= getAPCost(active, passive, c);
}

// Serialization

static default_constructor_func dcf2 = [](){ return new armor_item_wear(); };
static class_creator_inserter cci2("armor_item_wear", &dcf2);
std::string armor_item_wear::getClassName(){ return "armor_item_wear"; }
void armor_item_wear::saveToFile(savestream& svs)
{
	action::saveToFile(svs);
	svs.writeBytes(&dt, sizeof(dt));
	svs.writeBytes(&dr, sizeof(dr));
}
void armor_item_wear::loadFromFile(savestream& svs)
{
	action::loadFromFile(svs);
	svs.readBytes(&dt, sizeof(dt));
	svs.readBytes(&dr, sizeof(dr));
}
