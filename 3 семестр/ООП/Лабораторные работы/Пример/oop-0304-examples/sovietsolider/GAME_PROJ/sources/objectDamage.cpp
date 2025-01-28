#include "../headers/objectDamage.h"
#include "../headers/cell.h"
#include "../headers/field.h"

ObjectDamage::ObjectDamage()
{
	initView();
}


void ObjectDamage::onPass(Player& player, Field& field)
{
	if(pos_x == player.get_posx() && pos_y == player.get_posy())
	{
		player.set_damage(player.get_damage()+damageValue);
		if(player.get_damage() > 30)
			player.set_damage(30);
		//std::cout << "PLAYER DAMAGE: " << player.get_damage() << '\n';
		field.get_cell(pos_x, pos_y).clear_object();
	}

}

void ObjectDamage::initView()
{
	cv = new CellObjectView('D', *this);
}

void ObjectDamage::check_for_death(Field& field, std::vector <Object*>& objects, int i)
{
	if(!field.get_cell(pos_x, pos_y).get_has_object())
	{
		objects.erase(objects.begin() + i);
	}	
}

int ObjectDamage::get_pos_x() { return pos_x; }
int ObjectDamage::get_pos_y() { return pos_y; }

void ObjectDamage::set_pos_x(int pos) { pos_x = pos; }
void ObjectDamage::set_pos_y(int pos) { pos_y = pos; } 