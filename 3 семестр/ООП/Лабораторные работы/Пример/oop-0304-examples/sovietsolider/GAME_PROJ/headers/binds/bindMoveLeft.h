#ifndef BIND_MOVE_LEFT_H
#define BIND_MOVE_LEFT_H
#include "bindPlayer.h"

class BindMoveLeft : public BindPlayer
{
	private:
		char symb;
	public:
		BindMoveLeft(char c, Player* _player, Field* _field);
		void do_action();
		void set_symb(char s);
		char get_symb();
};


#endif