#ifndef EXIT_CONDITION_H
#define EXIT_CONDITION_H

#include "game_condition.h"
#include "../actors/player.h"

class exit_condition : public game_condition
{
	private:

	const player* plr;


	public:

	virtual bool isMet();
	void setPlayer(const player* plr);
};

#endif
