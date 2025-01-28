#ifndef BIND_MOVE_UP_H
#define BIND_MOVE_UP_H
#include "bindPlayer.h"

class BindMoveUp : public BindPlayer
{
	private:
		char symb;
	public:
		BindMoveUp(char c, Player* _player, Field* _field);
		void do_action();
		void set_symb(char s);
		char get_symb();
};


#endif