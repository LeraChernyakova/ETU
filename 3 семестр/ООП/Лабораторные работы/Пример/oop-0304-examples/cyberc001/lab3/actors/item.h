#ifndef ITEM_H
#define ITEM_H

#include "actor.h"

class item : public actor
{
	public:

	// events
	void onWalkedIn(actor& by_who);
	virtual void onUsed(actor& p) = 0;

	// properties

	size_t getAmount() const;
	void setAmount(size_t amount);

	actor& getOwner() const;
	void setOwner(actor* o);

	bool join(const item& other);


	protected:

	void initView();

	actor* owner;
	size_t amount;
};

#endif
