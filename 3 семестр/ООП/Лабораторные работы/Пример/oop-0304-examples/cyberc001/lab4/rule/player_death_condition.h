#ifndef PLAYER_DEATH_CONDITION
#define PLAYER_DEATH_CONDITION

#include "game_condition.h"
#include "../actors/player.h"

class player_death_condition : public game_condition
{
	private:

	const player* plr;


	public:

	virtual bool isMet();
	void setPlayer(const player* plr);
};

#endif
