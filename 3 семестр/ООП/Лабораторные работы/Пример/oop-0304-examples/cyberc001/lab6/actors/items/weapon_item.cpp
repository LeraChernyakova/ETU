#include "weapon_item.h"

#include <cstdlib>
#include <climits>

#include <sstream>
#include <string>
#include "../../logger/global_logger.h"

#include "../../save/class_creator_inserter.h"

weapon_item::weapon_item(size_t base_range, double base_accuracy)
	: base_range(base_range), base_accuracy(base_accuracy)
{
	actions.push_back(new weapon_item_fire(this, 18));
}

const char* weapon_item::getName() const { return "Weapon"; }

size_t weapon_item::getRange() { return base_range; }
double weapon_item::getAccuracy() { return base_accuracy; }

bool weapon_item::rollForHit()
{
	double roll = (double)std::rand() / RAND_MAX;
	return roll <= getAccuracy();
}

// weapon item serialization

static default_constructor_func dcf = [](){ return new weapon_item(); };
static class_creator_inserter cci("weapon_item", &dcf);
std::string weapon_item::getClassName(){ return "weapon_item"; }
void weapon_item::saveToFile(savestream& svs)
{
	item::saveToFile(svs);
	svs.writeBytes(&base_range, sizeof(base_range));
	svs.writeBytes(&base_accuracy, sizeof(base_accuracy));
}
void weapon_item::loadFromFile(savestream& svs)
{
	item::loadFromFile(svs);
	svs.readBytes(&base_range, sizeof(base_range));
	svs.readBytes(&base_accuracy, sizeof(base_accuracy));
	for(auto i = actions.begin(); i != actions.end(); ++i){
		weapon_item_fire* wif = dynamic_cast<weapon_item_fire*>(*i);
		if(wif)
			wif->setItem(this);
	}
}


// fire action

weapon_item_fire::weapon_item_fire(weapon_item* item, size_t damage)
	: item(item), damage(damage) {}

void weapon_item_fire::setItem(weapon_item* item) { this->item = item; }

const std::string weapon_item_fire::getName() { return "fire"; }

size_t weapon_item_fire::getAPCost(actor* active, actor* passive, cell* c)
{
	return 3;
}
bool weapon_item_fire::canExecute(size_t ap, actor* active, actor* passive, cell* c)
{
	if(ap < getAPCost(active, passive, c))
		return false;
	if(!active || !passive
	|| !active->hasParentCell() || !passive->hasParentCell())
		return false;

	size_t act_pas_dist = (std::max(active->getParentCell().get_x(), passive->getParentCell().get_x()) -
				std::min(active->getParentCell().get_x(), passive->getParentCell().get_x())) +
				(std::max(active->getParentCell().get_y(), passive->getParentCell().get_y()) -
				std::min(active->getParentCell().get_y(), passive->getParentCell().get_y()));
	if(item->getRange() < act_pas_dist)
		return false;

	return true;
}

void weapon_item_fire::execute(size_t& ap, actor* active, actor* passive, cell* c)
{
	if(!item->rollForHit()){
		std::stringstream ss;
		ss << active->getName() << " missed trying to shoot " << passive->getName();
		global_logger::message(GLOGGER_LEVEL_EVENT, ss.str());
		return;
	}

	size_t dmgdealt = passive->takeDamage(damage);
	ap -= getAPCost(active, passive, c);

	std::stringstream ss;
	ss << active->getName() << " fired a weapon at " << passive->getName() << " to deal " << dmgdealt << " damage";
	global_logger::message(GLOGGER_LEVEL_EVENT, ss.str());
}

// Serialization

static default_constructor_func dcf2 = [](){ return new weapon_item_fire(); };
static class_creator_inserter cci2("weapon_item_fire", &dcf2);
std::string weapon_item_fire::getClassName(){ return "weapon_item_fire"; }
void weapon_item_fire::saveToFile(savestream& svs)
{
	action::saveToFile(svs);
	svs.writeBytes(&damage, sizeof(damage));
}
void weapon_item_fire::loadFromFile(savestream& svs)
{
	action::loadFromFile(svs);
	svs.readBytes(&damage, sizeof(damage));
}
