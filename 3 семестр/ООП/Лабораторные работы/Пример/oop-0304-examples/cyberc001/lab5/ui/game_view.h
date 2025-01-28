#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <sstream>

#include "../game.h"

class game_view
{
	private:

	game& _game;
	std::stringstream game_log_buf;


	public:

	game_view(game& _game);

	game& getGame();

	// log buffer
	std::stringstream& getLogBuffer();
	void clearLogBuffer();

	// output
	void clear_screen();
	void refresh();
};

#endif
