#ifndef PLAYER_DEATH_CONDITION
#define PLAYER_DEATH_CONDITION

#include "game_condition.h"
#include "../actors/player.h"

class game;

class player_death_condition : public game_condition
{
	private:

	game* _game;


	public:

	virtual bool isMet();
	void setGame(game* _game);
};

#endif
