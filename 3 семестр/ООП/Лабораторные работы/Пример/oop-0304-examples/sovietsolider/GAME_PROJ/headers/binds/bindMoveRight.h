#ifndef BIND_MOVE_RIGHT_H
#define BIND_MOVE_RIGHT_H
#include "bindPlayer.h"

class BindMoveRight : public BindPlayer
{
	private:
		char symb;
	public:
		BindMoveRight(char c, Player* _player, Field* _field);
		void do_action();
		void set_symb(char s);
		char get_symb();
};


#endif