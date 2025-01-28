#include "../headers/inputController.h"

InputController::InputController(Player* _player, Field* _field, std::vector<Enemy*>* _enemies)
{
	player = _player; field = _field; enemies = _enemies;
}

void InputController::act()
{
	std::cin >> input_symb;
	for(int i=0; i<binds.size(); i++)
	{
		if(binds.at(i)->get_symb() == input_symb)
			binds.at(i)->do_action();
	}
}

void InputController::initialize_binds()
{
	binds.push_back(new BindMoveDown('s', player, field));binds.push_back(new BindMoveLeft('a', player, field));binds.push_back(new BindMoveRight('d', player, field));
	binds.push_back(new BindMoveUp('w', player, field)); binds.push_back(new BindFight(enemies, 'f', player, field)); binds.push_back(new BindExit('q'));
	/*for(int i=0; i<binds.size(); i++)
	{
		binds.at(i)->set_field(field);
		binds.at(i)->set_player(player);
	}*/
}

void InputController::set_player(Player* player)
{
	this->player = player;
}

void InputController::set_field(Field* field)
{
	this->field = field;
}

void InputController::set_enemies(std::vector<Enemy*>* enemy_container)
{
	enemies = enemy_container;
}

InputController::~InputController()
{
	
	for(int i=0; i<binds.size(); i++)
	{
		delete binds.at(i);
	}
	binds.clear();
}
