#include "weapon_item.h"

#include "../enemy.h"
#include "../player.h"

bool weapon_item::fire(actor* target)
{
	if(!owner)
		return false;

	size_t* apref;
	if(dynamic_cast<player*>(owner))
		apref = &dynamic_cast<player*>(owner)->getAP();
	else if(dynamic_cast<enemy*>(owner))
		apref = &dynamic_cast<enemy*>(owner)->getAP();
	if(!fire_action->canExecute(*apref, owner, target, &target->getParentCell()))
		return false;

	fire_action->execute(*apref, owner, target, &target->getParentCell());
	return true;
}
