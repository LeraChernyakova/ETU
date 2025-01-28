#include "action_move.h"

#include <sstream>
#include <string>
#include "../logger/global_logger.h"
#include "../field.h"

#include "../save/class_creator_inserter.h"

action_move::action_move(double ap_per_cell) : ap_per_cell(ap_per_cell) {}

size_t action_move::getAPCost(actor* active, actor* passive, cell* c)
{
	double total_ap_cost = 0.0;
	cell* curc = &active->getParentCell();
	while(curc->get_x() != c->get_x() || curc->get_y() != c->get_y())
	{
		if(curc->get_x() < c->get_x()
		&& curc->get_x() < curc->get_parent_field().get_w()-1
 		&& active->canMove(curc->get_parent_field().get_cell(curc->get_x() + 1, curc->get_y())))
			curc = &curc->get_parent_field().get_cell(curc->get_x() + 1, curc->get_y());
		else if(curc->get_x() > c->get_x()
		&& curc->get_x() > 0
		&& active->canMove(curc->get_parent_field().get_cell(curc->get_x() - 1, curc->get_y())))
			curc = &curc->get_parent_field().get_cell(curc->get_x() - 1, curc->get_y());
		else if(curc->get_y() < c->get_y()
		&& curc->get_y() < curc->get_parent_field().get_h()-1
		&& active->canMove(curc->get_parent_field().get_cell(curc->get_x(), curc->get_y() + 1)))
			curc = &curc->get_parent_field().get_cell(curc->get_x(), curc->get_y() + 1);
		else if(curc->get_y() > c->get_y()
		&& curc->get_y() > 0
		&& active->canMove(curc->get_parent_field().get_cell(curc->get_x(), curc->get_y() - 1)))
			curc = &curc->get_parent_field().get_cell(curc->get_x(), curc->get_y() - 1);
		else
			break;

		total_ap_cost += ap_per_cell;
	}

	return (size_t)total_ap_cost;
}
const std::string action_move::getName()
{
	return "move";
}
bool action_move::canExecute(size_t ap, actor* active, actor* passive, cell* c)
{
	if(ap < getAPCost(active, passive, c))
		return false;
	if(active == nullptr || c == nullptr)
		return false;
	return true;
}

void action_move::execute(size_t& ap, actor* active, actor* passive, cell* c)
{
	double total_ap_cost = 0.0;
	cell* curc = &active->getParentCell();
	while(curc->get_x() != c->get_x() || curc->get_y() != c->get_y())
	{
		if(curc->get_x() < c->get_x()
		&& curc->get_x() < curc->get_parent_field().get_w()-1
 		&& active->canMove(curc->get_parent_field().get_cell(curc->get_x() + 1, curc->get_y())))
			curc = &curc->get_parent_field().get_cell(curc->get_x() + 1, curc->get_y());
		else if(curc->get_x() > c->get_x()
		&& curc->get_x() > 0
		&& active->canMove(curc->get_parent_field().get_cell(curc->get_x() - 1, curc->get_y())))
			curc = &curc->get_parent_field().get_cell(curc->get_x() - 1, curc->get_y());
		else if(curc->get_y() < c->get_y()
		&& curc->get_y() < curc->get_parent_field().get_h()-1
		&& active->canMove(curc->get_parent_field().get_cell(curc->get_x(), curc->get_y() + 1)))
			curc = &curc->get_parent_field().get_cell(curc->get_x(), curc->get_y() + 1);
		else if(curc->get_y() > c->get_y()
		&& curc->get_y() > 0
		&& active->canMove(curc->get_parent_field().get_cell(curc->get_x(), curc->get_y() - 1)))
			curc = &curc->get_parent_field().get_cell(curc->get_x(), curc->get_y() - 1);
		else
			break;

		total_ap_cost += ap_per_cell;
		if((size_t)(total_ap_cost + ap_per_cell) > ap)
			break;
	}
	ap -= ((size_t)total_ap_cost);

	if(total_ap_cost > 0.0){
		std::stringstream ss;
		ss << active->getName() << " moved to (" << curc->get_x() << "; " << curc->get_y() << ")";
		global_logger::message(GLOGGER_LEVEL_EVENT, ss.str());
	}


	active->getParentCell().set_object(nullptr);
	active->setParentCell(curc);
	curc->set_object(active);
}

static default_constructor_func dcf = [](){ return new action_move(); };
static class_creator_inserter cci("action_move", &dcf);
std::string action_move::getClassName(){ return "action_move"; }
void action_move::saveToFile(savestream& svs)
{
	action::saveToFile(svs);
	svs.writeBytes(&ap_per_cell, sizeof(ap_per_cell));
}
void action_move::loadFromFile(savestream& svs)
{
	action::loadFromFile(svs);
	svs.readBytes(&ap_per_cell, sizeof(ap_per_cell));
}
