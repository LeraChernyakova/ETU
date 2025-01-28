#ifndef ARMOR_ITEM_H
#define ARMOR_ITEM_H

#include "../item.h"

class armor_item : public item
{
	public:

	armor_item(size_t dt, double dr);

	virtual void onUsed(actor& on_who);


	protected:

	bool worn;

	size_t dt; double dr;
};

#endif
