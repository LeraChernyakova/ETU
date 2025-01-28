#ifndef ARMOR_ITEM_H
#define ARMOR_ITEM_H

#include "../item.h"

class armor_item : public item
{
	public:

	armor_item(size_t dt = 0, double dr = 0);

	virtual const char* getName() const;

	bool isWorn() const;
	void setWorn(bool _worn);

	// serialization
	virtual std::string getClassName();
	virtual void saveToFile(savestream& svs);
	virtual void loadFromFile(savestream& svs);


	private:

	bool worn;
};

class armor_item_wear : public action
{
	public:

	armor_item_wear(armor_item* item = nullptr, size_t dt = 0, double dr = 0);

	void setItem(armor_item* item);

	virtual const std::string getName();
	virtual size_t getAPCost(actor* active, actor* passive, cell* c);
	virtual bool canExecute(size_t ap, actor* active, actor* passive, cell* c);

	virtual void execute(size_t& ap, actor* active, actor* passive, cell* c);

	virtual std::string getClassName();
	virtual void saveToFile(savestream& svs);
	virtual void loadFromFile(savestream& svs);


	private:

	armor_item* item;
	size_t dt; double dr;
};

#endif
