#ifndef BIND_H
#define BIND_H
#include "../player.h"

class Bind
{
	public:
		virtual char get_symb() = 0;
		virtual void set_symb(char s) = 0;
		virtual void do_action() = 0;
		virtual void set_player(Player* player);
		virtual void set_field(Field* field);
};

#endif