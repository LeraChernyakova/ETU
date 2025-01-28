#ifndef HEALTH_ITEM_H
#define HEALTH_ITEM_H

#include "../item.h"
#include "../../actions/action.h"

class health_item : public item
{
	public:

	health_item(size_t heal_amt = 0);

	virtual const char* getName() const;

	// serialization
	virtual std::string getClassName();
	virtual void loadFromFile(savestream& svs);
};

class health_item_heal : public action
{
	public:

	health_item_heal(health_item* item = nullptr, size_t heal_amt = 0);

	void setItem(health_item* item);

	virtual const std::string getName();
	virtual size_t getAPCost(actor* active, actor* passive, cell* c);
	virtual bool canExecute(size_t ap, actor* active, actor* passive, cell* c);

	virtual void execute(size_t& ap, actor* active, actor* passive, cell* c);

	virtual std::string getClassName();
	virtual void saveToFile(savestream& svs);
	virtual void loadFromFile(savestream& svs);

	private:

	health_item* item;
	size_t heal_amt;
};

#endif
