#include "enemy.h"

#include "../cell_object_view.h"

// Properties

void enemy::initView() { vw = new cell_object_view('&', *this); }

size_t& enemy::getAP() { return ap; }
const char* enemy::getName() const { return "Enemy"; }

// Events

void enemy::onAdd(cell& holder){}

void enemy::onTurn()
{
	ap = max_ap;

	std::vector<cell*> nc = getParentCell().get_neighbour_cells(detection_dist);
	actor* last_attack_target = nullptr;

	for(size_t i = 0; i < nc.size(); ++i)
	{
		cell* c = nc[i];
		if(!c->has_object())
			continue;
		actor* a = dynamic_cast<actor*>(&c->get_object());
		if(a == nullptr)
			continue;
		if(a->getTeamID() == getTeamID())
			continue;

		while(a != nullptr && a->getHealth() > 0
			&& atk_action->tryExecute(ap, this, a, c)){
			last_attack_target = a;
		}
	}

	if(last_attack_target == nullptr)
	{
		cell* target_cell = nullptr;
		actor* target = nullptr;
		size_t target_dist = (size_t)-1;

		for(size_t i = 0; i < nc.size(); ++i)
		{
			cell* c = nc[i];
			if(!c->has_object())
				continue;
			actor* a = dynamic_cast<actor*>(&c->get_object());
			if(a == nullptr)
				continue;
			if(a->getTeamID() == getTeamID())
				continue;

			if(a->getHealth() > 0 && c->get_distance(this->getParentCell()) < target_dist){
				target_cell = c;
				target = a;
				target_dist = c->get_distance(this->getParentCell());
			}
		}

		if(target)
			mv_action->tryExecute(ap, this, target, target_cell);
	}
}

void enemy::onDeath()
{
	getParentCell().set_object(nullptr);
}


void enemy::onWalkedIn(actor& by_who){}
void enemy::onWalkOn(cell& to_where){}
