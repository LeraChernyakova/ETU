#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "item.h"
#include "../actions/action_move.h"

class player : public actor
{
	public:

	player();
	~player();

	// Properites
	void setAP(size_t ap);
	void setMaxAP(size_t max_ap);
	size_t& getAP();

	virtual const char* getName() const;

	// Inventory
	bool addItemToInventory(item* i);
	std::vector<item*>::iterator getInventoryBegin();
	std::vector<item*>::iterator getInventoryEnd();

	// Events

	virtual void onTurn();

	// Input handling
	action& getMoveAction();

	// Serialization
	virtual std::string getClassName();
	virtual void saveToFile(savestream& svs);
	virtual void loadFromFile(savestream& svs);


	protected:

	virtual void initView();

	size_t ap, max_ap;

	std::vector<item*> inventory;
	size_t max_inventory_size = 10;

	action_move* mv_action;
};

#endif
