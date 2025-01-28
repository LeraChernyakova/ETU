#include "player_death_condition.h"

#include "../game.h"

bool player_death_condition::isMet()
{
	return _game->getMainPlayer().getHealth() <= 0;
}

void player_death_condition::setGame(game* _game) { this->_game = _game; }
