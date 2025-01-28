#include "action.h"

bool action::tryExecute(size_t& ap, actor* active, actor* passive, cell* c)
{
	if(!canExecute(ap, active, passive, c))
		return false;
	execute(ap, active, passive, c);
	return true;
}

void action::saveToFile(savestream& svs)
{
	serializable::saveToFile(svs);
}
void action::loadFromFile(savestream& svs)
{
	serializable::loadFromFile(svs);
}
