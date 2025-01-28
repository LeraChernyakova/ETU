#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "item.h"
#include "../actions/action_move.h"

class player : public actor
{
	public:

	player();

	// Properites
	size_t& getAP();

	virtual const char* getName() const;

	// Inventory
	bool addItemToInventory(item* i);

	// Events
	virtual void onAdd(cell& holder);

	virtual void onTurn();
	virtual void onDeath();

	virtual void onWalkedIn(actor& by_who);
	virtual void onWalkOn(cell& to_where);


	protected:

	virtual void initView();

	size_t ap, max_ap;

	std::vector<item*> inventory;
	size_t max_inventory_size = 10;

	action_move* mv_action;
};

#endif
