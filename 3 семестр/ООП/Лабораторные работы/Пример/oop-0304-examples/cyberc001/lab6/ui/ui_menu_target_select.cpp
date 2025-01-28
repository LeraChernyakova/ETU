#include "ui_menu_target_select.h"

#include "../logger/global_logger.h"
#include "../input/key_bind_manager.h"

ui_menu_target_select::ui_menu_target_select(action* action_select)
		: action_select(action_select) {}

std::tuple<actor*, cell*> ui_menu_target_select::getSelection() { return selection; }

void ui_menu_target_select::draw(game_view& _gvw) {}
void ui_menu_target_select::execute(game_view& _gvw, input_manager& inmngr)
{
	size_t x = _gvw.getGame().getMainPlayer().getParentCell().get_x(), y = _gvw.getGame().getMainPlayer().getParentCell().get_y();

	while(1){
	_gvw.getGame().getMainFieldView().setHighlight(true, x, y);
	_gvw.refresh();

	cell* c = &_gvw.getGame().getMainField().get_cell(x, y);
	actor* passive = c->has_object() ? &dynamic_cast<actor&>(c->get_object()) : nullptr;
	if(action_select->canExecute(_gvw.getGame().getMainPlayer().getAP(), &_gvw.getGame().getMainPlayer(), passive, c)){
		std::stringstream ss;
		ss << "Cost: " << action_select->getAPCost(&_gvw.getGame().getMainPlayer(), passive, c) << " AP";
		global_logger::message(GLOGGER_LEVEL_UI, ss.str());
	}
	else
		global_logger::message(GLOGGER_LEVEL_UI, "Cannot execute");

	std::string bind = key_bind_manager::get_bind(inmngr.get_key_input());

	if(bind == ""){
		global_logger::message(GLOGGER_LEVEL_UI, "This key is not bound to any action.");
		continue;
	}
	else if(bind == "menu_right"){
		if(y >= _gvw.getGame().getMainField().get_h())
			global_logger::message(GLOGGER_LEVEL_UI, "Cannot advance outside of the field.");
		else
			y++;
		continue;
	} else if(bind == "menu_left"){
		if(y == 0)
			global_logger::message(GLOGGER_LEVEL_UI, "Cannot advance outside of the field.");
		else
			y--;
		continue;
	} else if(bind == "menu_up"){
		if(x == 0)
			global_logger::message(GLOGGER_LEVEL_UI, "Cannot advance outside of the field.");
		else
			x--;
		continue;
	} else if(bind == "menu_down"){
		if(x >= _gvw.getGame().getMainField().get_w())
			global_logger::message(GLOGGER_LEVEL_UI, "Cannot advance outside of the field.");
		else
			x++;
		continue;
	}

	break;}
	_gvw.getGame().getMainFieldView().setHighlight(false);

	cell* c = &_gvw.getGame().getMainField().get_cell(x, y);
	selection = {c->has_object() ? &dynamic_cast<actor&>(c->get_object()) : nullptr, c};
}
