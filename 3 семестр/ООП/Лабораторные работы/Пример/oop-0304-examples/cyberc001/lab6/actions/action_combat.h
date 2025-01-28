#ifndef ACTION_COMBAT_H
#define ACTION_COMBAT_H

#include "action.h"

#include <cstddef>

class action_combat : public action
{
	public:

	action_combat(size_t base_dmg = 0);

	virtual size_t getDamageAmount(actor* active, actor* passive, cell* c);

	virtual bool canExecute(size_t ap_amt, actor* active, actor* passive, cell* c);
	void execute(size_t& ap_amt, actor* active, actor* passive, cell* c);

	virtual void saveToFile(savestream& svs);
	virtual void loadFromFile(savestream& svs);


	protected:

	size_t base_dmg;
};

#endif
