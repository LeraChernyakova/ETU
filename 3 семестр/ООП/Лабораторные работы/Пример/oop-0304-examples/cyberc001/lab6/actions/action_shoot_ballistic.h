#ifndef ACTION_SHOOT_BALLISTIC_H
#define ACTION_SHOOT_BALLISTIC_H

#include "action_combat.h"

class action_shoot_ballistic : public action_combat
{
	public:

	action_shoot_ballistic(size_t dmg = 0, size_t ap_cost = 0, size_t range = 0);

	const std::string getName();
	virtual size_t getAPCost(actor* active, actor* passive, cell* c);

	virtual bool canExecute(size_t ap_amt, actor* active, actor* passive, cell* c);

	virtual std::string getClassName();
	virtual void saveToFile(savestream& svs);
	virtual void loadFromFile(savestream& svs);


	protected:

	size_t ap_cost;
	size_t range;
};

#endif
