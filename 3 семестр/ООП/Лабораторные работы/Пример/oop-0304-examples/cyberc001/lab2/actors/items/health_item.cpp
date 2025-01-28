#include "health_item.h"

health_item::health_item(size_t heal_amt) : heal_amt(heal_amt) {}

void health_item::onUsed(actor& on_who)
{
	size_t healed = on_who.healDamage(heal_amt);
	if(healed){
		setAmount(getAmount() - 1);
	}
}
