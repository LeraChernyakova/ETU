#include "exit_condition.h"

#include "../cells/cell_exit.h"
#include "../game.h"

bool exit_condition::isMet()
{
	return _game->getMainPlayer().hasParentCell()
	&& (dynamic_cast<cell_exit*>(&_game->getMainPlayer().getParentCell()));
}

void exit_condition::setGame(game* _game) { this->_game = _game; }
