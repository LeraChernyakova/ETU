#ifndef UI_MENU_TARGET_SELECT_H
#define UI_MENU_TARGET_SELECT_H

#include "ui_menu.h"
#include "../actions/action.h"

class ui_menu_target_select : public ui_menu
{
	private:

	action* action_select;
	std::tuple<actor*, cell*> selection;


	public:

	ui_menu_target_select(action* action_select);

	std::tuple<actor*, cell*> getSelection();

	virtual void draw(game_view& _gvw);
	virtual void execute(game_view& _gvw, input_manager& inmngr);
};

#endif
