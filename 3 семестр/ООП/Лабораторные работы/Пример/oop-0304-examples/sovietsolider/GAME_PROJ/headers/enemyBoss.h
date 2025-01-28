#ifndef ENEMYBOSS_H
#define ENEMYBOSS_H
#include <unistd.h>
#include "enemy.h"
#include <iostream>

class EnemyBoss : public Enemy
{
	private:
		int health = 50, damage = 5;
		int pos_x = 0, pos_y = 0, range = 2;
		int count_of_move = 0;
		enum dir
		{
			Left, Right, Up, Down
		};
		dir move_dir = Left;
	public:
		EnemyBoss();
		bool seePlayer(Player& player);
		void init_fight(Player& player, Field& field);
		void move(Player& player, Field& field);
		void move_left(Player& player, Field& field);
		void move_right(Player& player, Field& field);
		void move_up(Player& player, Field& field);
		void move_down(Player& player, Field& field);
		void check_for_death(Field& field, std::vector <Enemy*>& enemies, int i);

		int get_pos_x() const;
		int get_pos_y() const;
		void set_pos_x(int pos);
		void set_pos_y(int pos);

		int get_health() const;
		void set_health(int health);
		int get_damage() const;
		void set_damage();

		void initView();
};


#endif // ENEMYBOSS_H
