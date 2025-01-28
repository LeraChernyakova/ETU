#ifndef EXIT_CONDITION_H
#define EXIT_CONDITION_H

#include "game_condition.h"
class game;

class exit_condition : public game_condition
{
	private:

	game* _game;


	public:

	virtual bool isMet();
	void setGame(game* _game);
};

#endif
