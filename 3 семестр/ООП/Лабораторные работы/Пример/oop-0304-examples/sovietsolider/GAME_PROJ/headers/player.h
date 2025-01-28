#ifndef PLAYER_H
#define PLAYER_H
#include "cellObject.h"
#include <ostream>
//#include "enemyInterface.h"
//#include "field.h"
class Cell; class Field; class Enemy;

class Player : public CellObject
{
	private:
		float health = 100, damage = 10;
		int pos_x, pos_y, range = 1;
	public:
		Player();

		int get_posx() const;
		int get_posy() const;
		void set_posx(int pos_x);
		void set_posy(int pos_y);

		float get_health() const;
		float get_damage() const;
		void set_health(float health);
		void set_damage(float damage);
		bool check_for_death(Field& field);

		void move_left(Field& field);
		void move_right(Field& field);
		void move_up(Field& field);
		void move_down(Field& field);

		bool see_enemy(Enemy* enemy, Field field);
		void init_fight(Enemy* enemy, Field field);

		int get_range() const;
		void set_range(int range);

		void initView();

		Cell& get_parent_cell();
		friend std::ostream& operator<<(std::ostream& os, const Player& actor); 

};

std::ostream& operator<<(std::ostream& os, const Player& actor);

#endif