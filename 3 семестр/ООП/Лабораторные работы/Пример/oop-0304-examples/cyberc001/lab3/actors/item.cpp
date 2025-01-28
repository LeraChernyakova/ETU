#include "item.h"

#include "../cell_object_view.h"
#include "player.h"

// events

void item::onWalkedIn(actor& by_who)
{
	player* p = dynamic_cast<player*>(&by_who);
	if(p){
		if(p->addItemToInventory(this)){
			if(hasParentCell()) getParentCell().set_object(nullptr);
		}
	}
}

// properties

void item::initView() { vw = new cell_object_view('+', *this); }

size_t item::getAmount() const { return amount; }
void item::setAmount(size_t amount)
{
	this->amount = amount;
	if(this->amount == 0) {
		if(hasParentCell()) getParentCell().set_object(nullptr);
	}
}

actor& item::getOwner() const { return *owner; }
void item::setOwner(actor* o) { owner = o; }

bool item::join(const item& other)
{
	if(typeid(other).hash_code() != typeid(*this).hash_code())
		return false;

	amount += other.getAmount();
	return true;
}
