#ifndef BIND_FIGHT_H
#define BIND_FIGHT_H
#include "bindPlayer.h"
#include "../enemy.h"
#include <vector>

class BindFight : public BindPlayer
{
	private:
		char symb;
		std::vector<Enemy*>* enemy_container;
	public:
		void do_action();
		void set_symb(char s);
		char get_symb();
		BindFight(std::vector<Enemy*>* enemies, char c, Player* _player, Field* _field);
};


#endif