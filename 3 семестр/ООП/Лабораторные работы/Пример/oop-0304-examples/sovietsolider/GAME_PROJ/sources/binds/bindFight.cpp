#include "/home/greenjoker/GAME_PROJ/headers/binds/bindFight.h"
#include "../../headers/field.h"

void BindFight::do_action()
{
	for(int i=0; i<enemy_container->size();i++)
	{
		player->init_fight(enemy_container->at(i), *field);
	}
}

char BindFight::get_symb()
{
	return symb;
}

void BindFight::set_symb(char s) { symb = s; }

BindFight::BindFight(std::vector<Enemy*>* enemies, char c, Player* _player, Field* _field) : BindPlayer(_player, _field), enemy_container(enemies), symb(c)
{}

