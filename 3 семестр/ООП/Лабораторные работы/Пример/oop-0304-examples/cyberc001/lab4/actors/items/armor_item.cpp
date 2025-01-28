#include "armor_item.h"

armor_item::armor_item(size_t dt, double dr) : dt(dt), dr(dr) {}

void armor_item::onUsed(actor& on_who)
{
	if(worn){
		on_who.setDamageThreshold(on_who.getDamageThreshold() + dt);
		on_who.setDamageResistance(on_who.getDamageResistance() + dr);
	}
	else{
		on_who.setDamageThreshold(on_who.getDamageThreshold() - dt);
		on_who.setDamageResistance(on_who.getDamageResistance() - dr);
	}

	worn = !worn;
}
