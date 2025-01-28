#include "/home/greenjoker/GAME_PROJ/headers/binds/bindMoveUp.h"

BindMoveUp::BindMoveUp(char c, Player* _player, Field* _field) : BindPlayer(_player, _field), symb(c) {}

void BindMoveUp::do_action()
{
	player->move_up(*field);
}

char BindMoveUp::get_symb()
{
	return symb;
}

void BindMoveUp::set_symb(char s) { symb = s; }
