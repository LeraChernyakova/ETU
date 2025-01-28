#include "player.h"

#include "../cell_object_view.h"
#include "../cells/cell_exit.h"

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
