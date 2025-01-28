#include "game_view.h"

#include "../input/key_bind_manager.h"
#include "../logger/global_logger.h"

#include <sstream>

game_view::game_view(game& _game) : _game(_game) {}


game& game_view::getGame() { return _game; }


std::stringstream& game_view::getLogBuffer() { return game_log_buf; }
void game_view::clearLogBuffer() { game_log_buf.str(""); }


void game_view::clear_screen()
{
	std::cout << "\033[H\033[J";
}

void game_view::refresh()
{
	clear_screen();
	_game.getMainFieldView().display();
	std::cout << game_log_buf.str();
	std::cout << '\n';
}
