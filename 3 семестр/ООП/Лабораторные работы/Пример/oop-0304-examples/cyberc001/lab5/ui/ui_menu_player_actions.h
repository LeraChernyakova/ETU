#ifndef UI_MENU_PLAYER_ACTIONS_H
#define UI_MENU_PLAYER_ACTIONS_H

#include "ui_menu.h"

class ui_menu_player_actions : public ui_menu
{
	private:

	size_t action_select_ind;
	action* action_select;
	size_t action_count;


	public:

	ui_menu_player_actions(size_t init_action_ind, action* init_action);

	virtual void draw(game_view& _gvw);
	virtual void execute(game_view& _gvw, input_manager& inmngr);
};

#endif
