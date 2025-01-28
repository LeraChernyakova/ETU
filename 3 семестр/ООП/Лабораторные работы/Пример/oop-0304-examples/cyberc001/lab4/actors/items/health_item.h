#ifndef HEALTH_ITEM_H
#define HEALTH_ITEM_H

#include "../item.h"

class health_item : public item
{
	public:

	health_item(size_t heal_amt);

	virtual void onUsed(actor& on_who);


	protected:

	size_t heal_amt;
};

#endif
