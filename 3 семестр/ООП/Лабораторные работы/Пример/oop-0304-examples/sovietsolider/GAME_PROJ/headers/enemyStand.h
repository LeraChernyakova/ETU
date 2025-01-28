#ifndef ENEMYSTAND_H
#define ENEMYSTAND_H
#include "enemy.h"
#include <iostream>


class EnemyStand : public Enemy
{
	private:
		int health = 77, damage = 2;
		int pos_x = 0, pos_y = 0, range = 1;
	public:
		EnemyStand();
		bool seePlayer(Player& player);
		void init_fight(Player& player, Field& field);
		void move(Player& player, Field& field);
		void check_for_death(Field& field, std::vector <Enemy*>& enemies, int i);

		int get_pos_x() const;
		int get_pos_y() const;
		void set_pos_x(int pos);
		void set_pos_y(int pos);

		int get_health() const;
		void set_health(int health);
		int get_damage() const;

		void initView();
};


#endif // ENEMYMOVE_H
