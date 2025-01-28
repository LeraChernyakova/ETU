#include "actor.h"

size_t actor::getHealth() { return health; }
void actor::setHealth(size_t hp) { health = hp; }
size_t actor::getMaxHealth() { return max_health; }
void actor::setMaxHealth(size_t max_hp) { max_health = max_hp; }
size_t actor::getDamageThreshold() { return dmg_thres; }
void actor::setDamageThreshold(size_t dmg_thres) { this->dmg_thres = dmg_thres; }
double actor::getDamageResistance() { return dmg_res; }
void actor::setDamageResistance(double dmg_res) { this->dmg_res = dmg_res; }

unsigned int actor::getTeamID() { return team_id; }
void actor::setTeamID(unsigned int tid) { this->team_id = tid; }

bool actor::canMove(cell& to_where)
{
	if(!to_where.is_passable())
		return false;
	if(to_where.has_object())
		return false;

	return true;
}

size_t actor::takeDamage(size_t dmg)
{
	size_t new_dmg = (dmg >= getDamageThreshold() ? dmg - getDamageThreshold() : 0)
			 * (1.0 - (getDamageResistance() >= 1.0 ? 1.0 : getDamageResistance()));
	setHealth(new_dmg < getHealth() ? getHealth() - new_dmg : 0);
	return new_dmg;
}
size_t actor::healDamage(size_t heal)
{
	setHealth(getMaxHealth() - getHealth() <= heal ? getHealth() + heal : getMaxHealth());
	return getMaxHealth() - getHealth() <= heal ? heal : getMaxHealth() - heal;
}
