#include "enemy.h"

#include "../cell_object_view.h"
#include "../save/class_creator_inserter.h"

enemy::enemy()
{
	initView();
}

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

// Serialization

static default_constructor_func dcf = [](){ return new enemy(); };
static class_creator_inserter cci("enemy", &dcf);
std::string enemy::getClassName(){ return "enemy"; }
void enemy::saveToFile(savestream& svs)
{
	actor::saveToFile(svs);
	svs.writeBytes(&ap, sizeof(ap));
	svs.writeBytes(&max_ap, sizeof(max_ap));
	svs.writeBytes(&detection_dist, sizeof(detection_dist));
	atk_action->saveToFile(svs);
	mv_action->saveToFile(svs);
}
void enemy::loadFromFile(savestream& svs)
{
	actor::loadFromFile(svs);
	svs.readBytes(&ap, sizeof(ap));
	svs.readBytes(&max_ap, sizeof(max_ap));
	svs.readBytes(&detection_dist, sizeof(detection_dist));
	atk_action = (action_combat*)class_creator::loadObject(svs);
	mv_action = (action_move*)class_creator::loadObject(svs);
}
