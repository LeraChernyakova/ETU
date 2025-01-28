#include "item.h"

#include "../save/class_creator_inserter.h"
#include "../cell_object_view.h"
#include "player.h"

item::~item()
{
	for(auto i = actions.begin(); i != actions.end(); ++i)
		delete *i;
}

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

std::vector<action*>::iterator item::getActionsBegin(){ return actions.begin(); }
std::vector<action*>::iterator item::getActionsEnd(){ return actions.end(); }

// serialization

static default_constructor_func dcf = [](){ return new item(); };
static class_creator_inserter cci("item", &dcf);
std::string item::getClassName(){ return "item"; }
void item::saveToFile(savestream& svs)
{
	actor::saveToFile(svs);
	svs.writeBytes(&amount, sizeof(amount));

	size_t actions_cnt = actions.size();
	svs.writeBytes(&actions_cnt, sizeof(actions_cnt));

	for(auto i = actions.begin(); i != actions.end(); ++i){
		(*i)->saveToFile(svs);
	}
}
void item::loadFromFile(savestream& svs)
{
	actor::loadFromFile(svs);
	svs.readBytes(&amount, sizeof(amount));

	size_t actions_cnt;
	svs.readBytes(&actions_cnt, sizeof(actions_cnt));

	for(auto i = actions.begin(); i != actions.end(); ++i)
		delete *i;
	actions.clear();
	for(size_t i = 0; i < actions_cnt; ++i){
		action* act = (action*)class_creator::loadObject(svs);
		actions.push_back(act);
	}
}
