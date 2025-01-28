#include "../headers/enemyStand.h"
#include "../headers/cell.h"
#include "../headers/field.h"
#include "../headers/logger.h"

EnemyStand::EnemyStand()
{
	initView();
}

bool EnemyStand::seePlayer(Player& player)
{
	if(std::abs(player.get_posx()-pos_x) <=range && std::abs(player.get_posy()-pos_y) <= range)
		return true;
	return false;
}

void::EnemyStand::init_fight(Player& player, Field& field)
{
	if(seePlayer(player))
	{
		//std::cout << player.get_health() << '\n';
		player.set_health(player.get_health()-damage);
		Logger::getGlobal().display(player, "Player took damage from Stand");
	}
}

void EnemyStand::check_for_death(Field& field, std::vector <Enemy*>& enemies, int i)
{
	if(health <=0)
	{
		field.get_cell(pos_x, pos_y).clear_enemy();
		field.get_cell(pos_x, pos_y).set_passable(true);
		enemies.erase(enemies.begin() + i);
	}
}

void EnemyStand::initView()
{
	cv = new CellObjectView('&', *this);
}

int EnemyStand::get_pos_x() const { return pos_x; }

int EnemyStand::get_pos_y() const { return pos_y; }

void EnemyStand::set_pos_x(int pos) { pos_x = pos; }

void EnemyStand::set_pos_y(int pos) { pos_y = pos; }

int EnemyStand::get_health() const { return health; }

void EnemyStand::set_health(int health) { this->health = health; }

void EnemyStand::move(Player& player, Field& field) {}

int EnemyStand::get_damage() const { return damage; }


