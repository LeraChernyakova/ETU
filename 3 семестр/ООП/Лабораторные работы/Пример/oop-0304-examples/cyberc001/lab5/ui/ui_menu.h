#ifndef UI_MENU_H
#define UI_MENU_H

#include "game_view.h"

class ui_menu
{
	public:

	virtual void draw(game_view& _gvw) = 0;
	virtual void execute(game_view& _gvw, input_manager& inmngr) = 0;
};

#endif
