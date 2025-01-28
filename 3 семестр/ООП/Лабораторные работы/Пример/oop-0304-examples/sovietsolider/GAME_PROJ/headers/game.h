#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "field_view.h"
#include <random>
#include "player.h"
#include <termios.h>
#include <unistd.h>
#include "enemy.h"
#include "enemyBoss.h"
#include "enemyMove.h"
#include "enemyStand.h"
#include "objectHeal.h"
#include "objectDamage.h"
#include "objectRange.h"
#include "object.h"
#include "inputController.h"

template <typename winCondType, typename lossCondType, int difficulty>
class Game
{
	public:
		void onStart();
		void Update();
		void clear_terminal_icanon();
		void set_terminal_icanon();
		void clear_screen();
		void initTermios(int echo);

		void input_control(char symb, Player& player, Field& field, std::vector<Enemy*> enemy_container);
		void spawn_enemy(std::vector<Enemy*>& enemy_container);

		std::vector<Enemy*>& get_enemies();
		Field& get_field();
		Player& get_player();

		winCondType& get_winCond();
		lossCondType& get_lossCond();
		~Game();

	private:
		std::vector<Enemy*> enemy_container;
		std::vector<Object*> objects_container;
		InputController* input_controller;
		

		winCondType winCond;
		lossCondType lossCond;
		
		Field* field;
		Player player;

};

#endif 
