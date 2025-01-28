#include "../headers/enemy.h"

std::ostream& operator<<(std::ostream& os, const Enemy& actor)
{
	os  << " health: " << actor.get_health()
		<< " damage: " << actor.get_damage()
		<< " PosX: " << actor.get_pos_x()
		<< " PosY: " << actor.get_pos_y();
	return os;
}


