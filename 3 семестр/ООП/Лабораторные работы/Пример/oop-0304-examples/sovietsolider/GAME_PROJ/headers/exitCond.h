#ifndef EXIT_COND_H
#define EXIT_COND_H

#include "gameCond.h"
#include "../headers/player.h"
#include "../headers/field.h"

template<int enemiesToWin>
class ExitCond : public GameCond
{
	private:
		Field* field;
		Player* player;
		std::vector <Enemy*>* enemies;
		int max_enemies_size;


	public:
		bool isDone();
		void setPlayer(Player& player);
		void setEnemies(std::vector<Enemy*>& enemies);
		void setField(Field& field);
};

#endif