#ifndef ACTOR_H
#define ACTOR_H

#include "../cell_object.h"
#include "../cells/cell.h"

class actor : public cell_object
{
	public:

	// Properties
	virtual size_t getHealth();
	virtual void setHealth(size_t hp);
	virtual size_t getMaxHealth();
	virtual void setMaxHealth(size_t max_hp);
	virtual size_t getDamageThreshold();
	virtual void setDamageThreshold(size_t dmg_thres);
	virtual double getDamageResistance();
	virtual void setDamageResistance(double dmg_res);

	virtual unsigned int getTeamID();
	virtual void setTeamID(unsigned int tid);

	// Events
	virtual void onTurn() = 0;

	virtual bool canMove(cell& to_where);

	virtual size_t takeDamage(size_t dmg);
	virtual size_t healDamage(size_t heal);
	virtual void onDeath() = 0;

	virtual void onWalkedIn(actor& by_who) = 0;
	virtual void onWalkOn(cell& to_where) = 0;


	private:

	size_t health, max_health;
	size_t dmg_thres;
	double dmg_res;

	unsigned int team_id;
};

#endif
