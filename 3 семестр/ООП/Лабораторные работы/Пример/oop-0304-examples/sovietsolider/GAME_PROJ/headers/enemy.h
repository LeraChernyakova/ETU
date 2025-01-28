#ifndef ENEMY_H
#define ENEMY_H
#include "player.h"
#include <iostream>
#include <vector>
#include "cellObject.h"
#include <ostream>




class Field; class Cell; 

class Enemy : public CellObject
{
	protected:
		std::string logString;
	public:
		virtual bool seePlayer(Player& player) = 0;
		virtual void init_fight(Player& player, Field& field) = 0;
		virtual void move(Player& player, Field& field) = 0;
		virtual void check_for_death(Field& field, std::vector <Enemy*>& enemies, int i) = 0;

		virtual int get_pos_x() const = 0;
		virtual int get_pos_y() const = 0;
		virtual void set_pos_x(int pos) = 0;
		virtual void set_pos_y(int pos) = 0;
		virtual void set_health(int Health) = 0;
		virtual int get_health() const = 0;
		virtual int get_damage() const = 0;
		
		friend std::ostream& operator<<(std::ostream& os, const Enemy& actor); 
};

std::ostream& operator<<(std::ostream& os, const Enemy& actor);

#endif