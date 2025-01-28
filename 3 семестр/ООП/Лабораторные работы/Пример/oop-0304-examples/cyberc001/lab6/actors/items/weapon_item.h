#ifndef WEAPON_ITEM_H
#define WEAPON_ITEM_H

#include "../item.h"
#include "../../actions/action_combat.h"

class weapon_item : public item
{
	public:

	weapon_item(size_t base_range = 0, double base_accuracy = 0);

	virtual const char* getName() const;

	virtual size_t getRange();
	virtual double getAccuracy();

	virtual bool rollForHit();

	virtual std::string getClassName();
	virtual void saveToFile(savestream& svs);
	virtual void loadFromFile(savestream& svs);


	protected:

	size_t base_range;
	double base_accuracy;
};

class weapon_item_fire : public action
{
	public:

	weapon_item_fire(weapon_item* item = nullptr, size_t damage = 0);

	void setItem(weapon_item* item);

	virtual const std::string getName();
	virtual size_t getAPCost(actor* active, actor* passive, cell* c);
	virtual bool canExecute(size_t ap, actor* active, actor* passive, cell* c);

	virtual void execute(size_t& ap, actor* active, actor* passive, cell* c);

	virtual std::string getClassName();
	virtual void saveToFile(savestream& svs);
	virtual void loadFromFile(savestream& svs);


	private:

	weapon_item* item;
	size_t damage;
};

#endif
