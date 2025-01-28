#include "../headers/objectHeal.h"
#include "../headers/cell.h"
#include "../headers/field.h"

ObjectHeal::ObjectHeal()
{
	initView();
}


void ObjectHeal::onPass(Player& player, Field& field)
{
	if(pos_x == player.get_posx() && pos_y == player.get_posy())
	{
		player.set_health(player.get_health()+healValue);
		field.get_cell(pos_x, pos_y).clear_object();
	}
	
}

void ObjectHeal::initView()
{
	cv = new CellObjectView('H', *this);
}

void ObjectHeal::check_for_death(Field& field, std::vector <Object*>& objects, int i)
{
	if(!field.get_cell(pos_x, pos_y).get_has_object())
	{
		objects.erase(objects.begin() + i);
	}	
}

int ObjectHeal::get_pos_x() { return pos_x; }
int ObjectHeal::get_pos_y() { return pos_y; }

void ObjectHeal::set_pos_x(int pos) { pos_x = pos; }
void ObjectHeal::set_pos_y(int pos) { pos_y = pos; } 