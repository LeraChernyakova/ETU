#ifndef DEATH_COND_H
#define DEATH_COND_H
#include "gameCond.h"
#include "player.h"

template<int death_health>
class DeathCond : public GameCond
{
	private:
		Player* player;
	public:
		bool isDone();
		void setPlayer(Player& player);
};

#endif