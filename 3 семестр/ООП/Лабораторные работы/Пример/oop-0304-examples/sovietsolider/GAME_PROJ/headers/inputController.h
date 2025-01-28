#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H
#include <vector>
#include "../headers/binds/bindPlayer.h"
#include "../headers/binds/bindMoveDown.h"
#include "../headers/binds/bindMoveLeft.h"
#include "../headers/binds/bindMoveRight.h"
#include "../headers/binds/bindMoveUp.h"
#include "../headers/binds/bindFight.h"
#include "../headers/binds/bind.h"
#include "../headers/binds/bindExit.h"


class InputController
{
	private:
		char input_symb;
		std::vector<Bind*> binds;
		std::vector<Enemy*>* enemies;
		Player* player;
		Field* field;
	public:
		InputController(Player* _player, Field* _field, std::vector<Enemy*>* _enemies);
		void act();
		void initialize_binds();
		void set_player(Player* player);
		void set_field(Field* field);
		void set_enemies(std::vector<Enemy*>* enemy_container);
		~InputController();
};

#endif