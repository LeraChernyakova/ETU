#ifndef BIND_MOVE_DOWN_H
#define BIND_MOVE_DOWN_H
#include "bindPlayer.h"

class BindMoveDown : public BindPlayer
{
	private:
		char symb;
	public:
		BindMoveDown(char c, Player* _player, Field* _field);
		void do_action();
		void set_symb(char s);
		char get_symb();
};


#endif