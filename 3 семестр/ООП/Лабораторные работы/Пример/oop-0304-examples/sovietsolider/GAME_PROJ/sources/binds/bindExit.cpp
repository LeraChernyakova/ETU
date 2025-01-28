#include "/home/greenjoker/GAME_PROJ/headers/binds/bindExit.h"

BindExit::BindExit(char c) : symb(c) {}

void BindExit::do_action()
{
	exit(0);
}

char BindExit::get_symb()
{
	return symb;
}

void BindExit::set_symb(char s) { symb = s; }
