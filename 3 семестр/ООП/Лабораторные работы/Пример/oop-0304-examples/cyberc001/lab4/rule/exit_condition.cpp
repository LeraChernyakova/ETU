#include "exit_condition.h"

#include "../cells/cell_exit.h"

bool exit_condition::isMet()
{
	return plr
	&& plr->hasParentCell()
	&& (dynamic_cast<cell_exit*>(&plr->getParentCell()));
}

void exit_condition::setPlayer(const player* plr) { this->plr = plr; }
