#include "../headers/objectRange.h"
#include "../headers/objectHeal.h"
#include "../headers/cell.h"
#include "../headers/field.h"

ObjectRange::ObjectRange()
{
	initView();
}


void ObjectRange::onPass(Player& player, Field& field)
{
	if(pos_x == player.get_posx() && pos_y == player.get_posy())
	{
		player.set_range(player.get_range()+rangeValue);
		if(player.get_range() > 2)
			player.set_range(2);
		//std::cout << "RANGE VALUE:" << player.get_range() << std::endl;
		field.get_cell(pos_x, pos_y).clear_object();
	}
}

void ObjectRange::initView()
{
	cv = new CellObjectView('R', *this);
}

void ObjectRange::check_for_death(Field& field, std::vector <Object*>& objects, int i)
{
	if(!field.get_cell(pos_x, pos_y).get_has_object())
	{
		objects.erase(objects.begin() + i);
	}	
}

int ObjectRange::get_pos_x() { return pos_x; }
int ObjectRange::get_pos_y() { return pos_y; }

void ObjectRange::set_pos_x(int pos) { pos_x = pos; }
void ObjectRange::set_pos_y(int pos) { pos_y = pos; } 