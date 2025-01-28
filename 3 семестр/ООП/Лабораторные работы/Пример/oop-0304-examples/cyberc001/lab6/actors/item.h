#ifndef ITEM_H
#define ITEM_H

#include "actor.h"
#include "../actions/action.h"
#include <vector>

class item : public actor
{
	public:

	virtual ~item();

	// events
	void onWalkedIn(actor& by_who);

	// properties

	size_t getAmount() const;
	void setAmount(size_t amount);

	actor& getOwner() const;
	void setOwner(actor* o);

	bool join(const item& other);

	std::vector<action*>::iterator getActionsBegin();
	std::vector<action*>::iterator getActionsEnd();

	// serialization

	virtual std::string getClassName();
	virtual void saveToFile(savestream& svs);
	virtual void loadFromFile(savestream& svs);


	protected:

	void initView();

	actor* owner;
	size_t amount = 1;

	std::vector<action*> actions;
};

#endif
