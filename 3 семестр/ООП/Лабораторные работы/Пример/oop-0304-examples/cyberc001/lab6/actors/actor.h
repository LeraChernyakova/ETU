#ifndef ACTOR_H
#define ACTOR_H

#include "../cell_object.h"
#include "../cells/cell.h"
#include "../logger/observable.h"

class actor : public cell_object, public observable
{
	public:

	// Properties
	virtual size_t getHealth() const;
	virtual void setHealth(size_t hp);
	virtual size_t getMaxHealth() const;
	virtual void setMaxHealth(size_t max_hp);
	virtual size_t getDamageThreshold() const;
	virtual void setDamageThreshold(size_t dmg_thres);
	virtual double getDamageResistance() const;
	virtual void setDamageResistance(double dmg_res);

	virtual unsigned int getTeamID() const;
	virtual void setTeamID(unsigned int tid);
	virtual const char* getName() const;

	// Events
	virtual void onTurn();

	virtual bool canMove(cell& to_where);

	virtual size_t takeDamage(size_t dmg);
	virtual size_t healDamage(size_t heal);
	virtual void onDeath();

	virtual void onWalkedIn(actor& by_who);
	virtual void onWalkOn(cell& to_where);

	// Text output
	friend std::ostream& operator<<(std::ostream& os, const actor& ac);

	// Serialization
	virtual std::string getClassName();
	virtual void saveToFile(savestream& svs);
	virtual void loadFromFile(savestream& svs);


	private:

	size_t health = 0, max_health = 0;
	size_t dmg_thres = 0;
	double dmg_res = 0.;

	unsigned int team_id = 0;
};

std::ostream& operator<<(std::ostream& os, const actor& ac);

#endif
