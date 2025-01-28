#ifndef HEALTH_ITEM_H
#define HEALTH_ITEM_H

#include "../item.h"
#include "../../actions/action.h"

class health_item : public item
{
	public:

	health_item(size_t heal_amt);

	virtual const char* getName() const;
};

class health_item_heal : public action
{
	public:

	health_item_heal(health_item& item, size_t heal_amt);

	virtual const std::string getName();
	virtual size_t getAPCost(actor* active, actor* passive, cell* c);
	virtual bool canExecute(size_t ap, actor* active, actor* passive, cell* c);

	virtual void execute(size_t& ap, actor* active, actor* passive, cell* c);


	private:

	health_item& item;
	size_t heal_amt;
};

#endif
