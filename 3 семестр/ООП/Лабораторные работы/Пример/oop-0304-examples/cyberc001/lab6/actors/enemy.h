#ifndef ENEMY_H
#define ENEMY_H

#include "actor.h"
#include "../actions/action_combat.h"
#include "../actions/action_move.h"

#include <vector>

class enemy : public actor
{
	public:

	enemy();

	// Properties
	size_t& getAP();

	virtual const char* getName() const;

	// Events
	virtual void onAdd(cell& holder);

	virtual void onTurn();
	virtual void onDeath();

	virtual void onWalkedIn(actor& by_who);
	virtual void onWalkOn(cell& to_where);

	// Serialization
	virtual std::string getClassName();
	virtual void saveToFile(savestream& svs);
	virtual void loadFromFile(savestream& svs);


	protected:

	virtual void initView();

	size_t ap, max_ap;

	size_t detection_dist;

	action_combat* atk_action;
	action_move* mv_action;
};

#endif
