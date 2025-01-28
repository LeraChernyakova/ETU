#include "player.h"

#include "../cell_object_view.h"
#include "../cells/cell_exit.h"

#include "../save/class_creator_inserter.h"

player::player()
{
	initView();

	mv_action = new action_move(2.2);
}
player::~player()
{
	delete mv_action;

	for(auto i = inventory.begin(); i != inventory.end(); ++i)
		delete *i;
}

// Properties

void player::initView() { vw = new cell_object_view('@', *this); }

void player::setAP(size_t ap) { this->ap = ap; }
void player::setMaxAP(size_t max_ap) { this->max_ap = max_ap; }
size_t& player::getAP() { return ap; }

const char* player::getName() const { return "Player"; }


// Inventory

bool player::addItemToInventory(item* i)
{
	for(size_t j = 0; j < inventory.size(); ++j)
		if(inventory[j]->join(*i))
			return true;

	if(inventory.size() >= max_inventory_size)
		return false;

	inventory.push_back(i);
	i->setOwner(this);
	return true;
}

std::vector<item*>::iterator player::getInventoryBegin() { return inventory.begin(); }
std::vector<item*>::iterator player::getInventoryEnd() { return inventory.end(); }


// Events

void player::onTurn()
{
	ap = max_ap;
}


// Input handling

action& player::getMoveAction() { return *mv_action; }


// Serialization

static default_constructor_func dcf = [](){ return new player(); };
static class_creator_inserter cci("player", &dcf);
std::string player::getClassName(){ return "player"; }
void player::saveToFile(savestream& svs)
{
	actor::saveToFile(svs);
	svs.writeBytes(&ap, sizeof(ap));
	svs.writeBytes(&max_ap, sizeof(max_ap));
	svs.writeBytes(&max_inventory_size, sizeof(max_inventory_size));

	mv_action->saveToFile(svs);

	size_t inv_sz = inventory.size();
	svs.writeBytes(&inv_sz, sizeof(inv_sz));
	for(auto i = inventory.begin(); i != inventory.end(); ++i){
		if(*i){
			(*i)->saveToFile(svs);
		}
	}
}
void player::loadFromFile(savestream& svs)
{
	actor::loadFromFile(svs);
	svs.readBytes(&ap, sizeof(ap));
	svs.readBytes(&max_ap, sizeof(max_ap));
	svs.readBytes(&max_inventory_size, sizeof(max_inventory_size));

	mv_action = (action_move*)class_creator::loadObject(svs);

	size_t inv_sz;
	svs.readBytes(&inv_sz, sizeof(inv_sz));
	for(size_t i = 0; i < inv_sz; ++i){
		item* inv = (item*)class_creator::loadObject(svs);
		addItemToInventory(inv);
	}
}
