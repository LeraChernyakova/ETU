#include "/home/greenjoker/GAME_PROJ/headers/binds/bindMoveLeft.h"

BindMoveLeft::BindMoveLeft(char c, Player* _player, Field* _field) : BindPlayer(_player, _field), symb(c) {}

void BindMoveLeft::do_action()
{
	player->move_left(*field);
}

char BindMoveLeft::get_symb()
{
	return symb;
}

void BindMoveLeft::set_symb(char s) { symb = s; }