#ifndef GAME_UI_H
#define GAME_UI_H

#include "game.h"

class game_ui
{
	private:

	game& _game;

	size_t action_select_ind;
	action* action_select;
	size_t action_count;


	public:

	game_ui(game& _game, size_t init_action_ind, action* init_action);

	// output
	void draw_player_actions();

	// input
	void handle_action_menu(input_manager& inmngr);
	std::tuple<actor*, cell*> select_action_target(input_manager& inmngr);
};

#endif
