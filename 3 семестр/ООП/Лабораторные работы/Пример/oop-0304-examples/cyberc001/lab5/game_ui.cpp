#include "game_ui.h"

#include "input/key_bind_manager.h"

game_ui::game_ui(game& _game, size_t init_action_ind, action* init_action)
	: _game(_game), action_select_ind(init_action_ind), action_select(init_action) {}

void game_ui::draw_player_actions()
{
	action_count = 1;
	std::cout << "AP: " << _game.getMainPlayer().getAP() << '\n';
	std::cout << "Avaliable actions:\n";

	if(action_select_ind == 0){
		std::cout << "** " << _game.getMainPlayer().getMoveAction().getName() << " **\n";
		action_select = &_game.getMainPlayer().getMoveAction();
	}
	else
		std::cout << _game.getMainPlayer().getMoveAction().getName() << '\n';

	for(auto i = _game.getMainPlayer().getInventoryBegin(); i != _game.getMainPlayer().getInventoryEnd(); ++i){
		if(!*i) continue;
		for(auto j = (*i)->getActionsBegin(); j != (*i)->getActionsEnd(); ++j){
			std::cout << (*i)->getName() << " | ";
			if(action_count == action_select_ind){
				std::cout << "** " << (*j)->getName() << " **\n";
				action_select = *j;
			}
			else
				std::cout << (*j)->getName() << '\n';
			++action_count;
		}
	}
}

void game_ui::handle_action_menu(input_manager& inmngr)
{
	std::string bind;

	while(1){
	bind = key_bind_manager::get_bind(inmngr.get_key_input());

	if(bind == ""){
		_game.refresh(*this);
		std::cout << "This key is not bound to any action.\n";
		continue;
	}
	else if(bind == "menu_down"){
		if(action_select_ind + 1 < action_count)
			++action_select_ind;
		_game.refresh(*this);
		continue;
	}
	else if(bind == "menu_up"){
		if(action_select_ind > 0)
			--action_select_ind;
		_game.refresh(*this);
		continue;
	}
	else if(bind == "end_turn"){
		_game.refresh(*this);
		break;
	}
	else if(bind == "confirm"){
		std::tuple<actor*, cell*> action_info = select_action_target(inmngr);
		if(!action_select->canExecute(_game.getMainPlayer().getAP(), &_game.getMainPlayer(),
							std::get<0>(action_info), std::get<1>(action_info))){
			std::cout << "Cannot execute this action.\n";
			continue;
		}
		action_select->tryExecute(_game.getMainPlayer().getAP(), &_game.getMainPlayer(),
							std::get<0>(action_info), std::get<1>(action_info));
		_game.refresh(*this);
		continue;
	}
	else{
		_game.refresh(*this);
		continue;
	}
	break;}
}

std::tuple<actor*, cell*> game_ui::select_action_target(input_manager& inmngr)
{
	size_t x = _game.getMainPlayer().getParentCell().get_x(), y = _game.getMainPlayer().getParentCell().get_y();

	while(1){
	_game.getMainFieldView().setHighlight(true, x, y);
	_game.refresh(*this);

	cell* c = &_game.getMainField().get_cell(x, y);
	actor* passive = c->has_object() ? &dynamic_cast<actor&>(c->get_object()) : nullptr;
	if(action_select->canExecute(_game.getMainPlayer().getAP(), &_game.getMainPlayer(), passive, c))
		std::cout << "Cost: " << action_select->getAPCost(&_game.getMainPlayer(), passive, c) << " AP\n";
	else
		std::cout << "Cannot execute\n";

	std::string bind = key_bind_manager::get_bind(inmngr.get_key_input());

	if(bind == ""){
		std::cout << "This key is not bound to any action.\n";
		continue;
	}
	else if(bind == "menu_right"){
		if(y >= _game.getMainField().get_h()){
			std::cout << "Cannot advance outside of the field.\n";
		}
		else{
			y++;
		}
		continue;
	} else if(bind == "menu_left"){
		if(y == 0){
			std::cout << "Cannot advance outside of the field.\n";
		}
		else{
			y--;
		}
		continue;
	} else if(bind == "menu_up"){
		if(x == 0){
			std::cout << "Cannot advance outside of the field.\n";
		}
		else{
			x--;
		}
		continue;
	} else if(bind == "menu_down"){
		if(x >= _game.getMainField().get_w()){
			std::cout << "Cannot advance outside of the field.\n";
		}
		else{
			x++;
		}
		continue;
	}

	break;}
	_game.getMainFieldView().setHighlight(false);

	cell* c = &_game.getMainField().get_cell(x, y);
	return {c->has_object() ? &dynamic_cast<actor&>(c->get_object()) : nullptr,
		c};
}
