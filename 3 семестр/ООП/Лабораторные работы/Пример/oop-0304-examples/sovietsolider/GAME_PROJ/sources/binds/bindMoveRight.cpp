#include "/home/greenjoker/GAME_PROJ/headers/binds/bindMoveRight.h"

BindMoveRight::BindMoveRight(char c, Player* _player, Field* _field) : BindPlayer(_player, _field), symb(c) {}

void BindMoveRight::do_action()
{
	player->move_right(*field);
}

char BindMoveRight::get_symb()
{
	return symb;
}

void BindMoveRight::set_symb(char s) { symb = s; }

