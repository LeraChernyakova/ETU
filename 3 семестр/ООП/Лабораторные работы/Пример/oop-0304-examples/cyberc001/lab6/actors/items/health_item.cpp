#include "health_item.h"

#include <sstream>
#include <string>
#include "../../logger/global_logger.h"

#include "../../save/class_creator_inserter.h"

health_item::health_item(size_t heal_amt)
{
	actions.push_back(new health_item_heal(this, heal_amt));
}

const char* health_item::getName() const { return "Healing item"; }

// heal item serialization

static default_constructor_func dcf = [](){ return new health_item(); };
static class_creator_inserter cci("health_item", &dcf);
std::string health_item::getClassName(){ return "health_item"; }
void health_item::loadFromFile(savestream& svs)
{
	item::loadFromFile(svs);
	for(auto i = actions.begin(); i != actions.end(); ++i){
		health_item_heal* hih = dynamic_cast<health_item_heal*>(*i);
		if(hih)
			hih->setItem(this);
	}
}


// heal action

health_item_heal::health_item_heal(health_item* item, size_t heal_amt)
	: heal_amt(heal_amt), item(item) {}

void health_item_heal::setItem(health_item* item) { this->item = item; }

const std::string health_item_heal::getName() { return "apply healing"; }

size_t health_item_heal::getAPCost(actor* active, actor* passive, cell* c)
{
	return 2;
}
bool health_item_heal::canExecute(size_t ap, actor* active, actor* passive, cell* c)
{
	if(ap < getAPCost(active, passive, c))
		return false;
	if(item->getAmount() == 0)
		return false;
	if(!passive)
		return false;
	if(passive->getHealth() >= passive->getMaxHealth())
		return false;

	return true;
}

void health_item_heal::execute(size_t& ap, actor* active, actor* passive, cell* c)
{
	size_t heal_amt = passive->healDamage(heal_amt);
	item->setAmount(item->getAmount() - 1);

	ap -= getAPCost(active, passive, c);

	std::stringstream ss;
	ss << active->getName() << " healed " << passive->getName() << " for " << heal_amt << " damage";
	global_logger::message(GLOGGER_LEVEL_EVENT, ss.str());
}

// Serialization

static default_constructor_func dcf2 = [](){ return new health_item_heal(); };
static class_creator_inserter cci2("health_item_heal", &dcf2);
std::string health_item_heal::getClassName(){ return "health_item_heal"; }
void health_item_heal::saveToFile(savestream& svs)
{
	action::saveToFile(svs);
	svs.writeBytes(&heal_amt, sizeof(heal_amt));
}
void health_item_heal::loadFromFile(savestream& svs)
{
	action::loadFromFile(svs);
	svs.readBytes(&heal_amt, sizeof(heal_amt));
}
