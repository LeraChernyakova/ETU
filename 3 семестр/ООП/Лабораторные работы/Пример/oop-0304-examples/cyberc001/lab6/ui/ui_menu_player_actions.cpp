#include "ui_menu_player_actions.h"
#include "ui_menu_target_select.h"

#include "../logger/global_logger.h"
#include "../input/key_bind_manager.h"

ui_menu_player_actions::ui_menu_player_actions(size_t init_action_ind, action* init_action)
	: action_select_ind(init_action_ind), action_select(init_action) {}


void ui_menu_player_actions::draw(game_view& _gvw)
{
	std::stringstream ss;
	ss << "AP: " << _gvw.getGame().getMainPlayer().getAP();
	global_logger::message(GLOGGER_LEVEL_UI, ss.str());
	global_logger::message(GLOGGER_LEVEL_UI, "Avaliable actions:");

	action_count = 1;
	if(action_select_ind == 0){
		ss.str("");
		ss << "** " << _gvw.getGame().getMainPlayer().getMoveAction().getName() << " **";
		global_logger::message(GLOGGER_LEVEL_UI, ss.str());
		action_select = &_gvw.getGame().getMainPlayer().getMoveAction();
	}
	else{
		ss.str("");
		ss << _gvw.getGame().getMainPlayer().getMoveAction().getName();
		global_logger::message(GLOGGER_LEVEL_UI, ss.str());
	}

	for(auto i = _gvw.getGame().getMainPlayer().getInventoryBegin(); i != _gvw.getGame().getMainPlayer().getInventoryEnd(); ++i){
		if(!*i) continue;
		for(auto j = (*i)->getActionsBegin(); j != (*i)->getActionsEnd(); ++j){
			ss.str("");
			ss << (*i)->getName() << " | ";
			if(action_count == action_select_ind){
				ss << "** " << (*j)->getName() << " **";
				action_select = *j;
			}
			else
				ss << (*j)->getName();
			global_logger::message(GLOGGER_LEVEL_UI, ss.str());
			++action_count;
		}
	}
}

void ui_menu_player_actions::execute(game_view& _gvw, input_manager& inmngr)
{
	_gvw.refresh(); draw(_gvw);

	std::string bind;

	while(1){
	bind = key_bind_manager::get_bind(inmngr.get_key_input());

	if(bind == ""){
		_gvw.refresh(); draw(_gvw);
		global_logger::message(GLOGGER_LEVEL_UI, "This key is not bound to any action.");
		continue;
	}
	else if(bind == "menu_down"){
		if(action_select_ind + 1 < action_count)
			++action_select_ind;
		_gvw.refresh(); draw(_gvw);
		continue;
	}
	else if(bind == "menu_up"){
		if(action_select_ind > 0)
			--action_select_ind;
		_gvw.refresh(); draw(_gvw);
		continue;
	}
	else if(bind == "end_turn"){
		_gvw.refresh(); draw(_gvw);
		break;
	}
	else if(bind == "confirm"){
		ui_menu_target_select menu_target(action_select);
		menu_target.execute(_gvw, inmngr);
		std::tuple<actor*, cell*> action_info = menu_target.getSelection();
		if(!action_select->canExecute(_gvw.getGame().getMainPlayer().getAP(), &_gvw.getGame().getMainPlayer(),
							std::get<0>(action_info), std::get<1>(action_info))){
			global_logger::message(GLOGGER_LEVEL_UI, "Cannot execute this action.");
			continue;
		}
		action_select->tryExecute(_gvw.getGame().getMainPlayer().getAP(), &_gvw.getGame().getMainPlayer(),
							std::get<0>(action_info), std::get<1>(action_info));
		_gvw.refresh(); draw(_gvw);
		continue;
	}
	else if(bind == "save"){
		_gvw.refresh(); draw(_gvw);
		global_logger::message(GLOGGER_LEVEL_UI, "Enter save file to save to:");
		std::string fname = inmngr.get_line();

		if(_gvw.getGame().save(fname))
		{ _gvw.refresh(); draw(_gvw); }
		continue;
	}
	else if(bind == "load"){
		_gvw.refresh(); draw(_gvw);
		global_logger::message(GLOGGER_LEVEL_UI, "Enter save file to load from:");
		std::string fname = inmngr.get_line();

		if(_gvw.getGame().load(fname))
		{ _gvw.refresh(); draw(_gvw); }
		continue;
	}
	else{
		_gvw.refresh(); draw(_gvw);
		continue;
	}
	break;}

}
