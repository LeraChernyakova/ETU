#include "/home/greenjoker/GAME_PROJ/headers/binds/bindMoveDown.h"

BindMoveDown::BindMoveDown(char c, Player* _player, Field* _field) : BindPlayer(_player, _field), symb(c) {}


void BindMoveDown::do_action()
{
	player->move_down(*field);
}

char BindMoveDown::get_symb()
{
	return symb;
}

void BindMoveDown::set_symb(char s) { symb = s; }

