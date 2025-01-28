#include "../headers/enemyBoss.h"
#include "../headers/cell.h"
#include "../headers/field.h"
#include "../headers/logger.h"

EnemyBoss::EnemyBoss()
{
	initView();
}

bool EnemyBoss::seePlayer(Player& player)
{
	if(std::abs(player.get_posx()-pos_x) <=range && std::abs(player.get_posy()-pos_y) <= range)
		return true;
	return false;
}

void::EnemyBoss::init_fight(Player& player, Field& field)
{
	if(seePlayer(player) && health!=0)
	{
		//std::cout<< "IM INIT";
		//std::cout << "PLAYER HEALTH " << player.get_health() << '\n';
		player.set_health(player.get_health()-damage);
		Logger::getGlobal().display(player, "Player took damage from Boss");
	}
}

void EnemyBoss::check_for_death(Field& field, std::vector <Enemy*>& enemies,  int i)
{
	if(health <=0)
	{
		field.get_cell(pos_x, pos_y).clear_enemy();
		field.get_cell(pos_x, pos_y).set_passable(true);
		enemies.erase(enemies.begin() + i);
	}
}

void EnemyBoss::move_left(Player& player, Field& field)
{
	if(!field.get_cell(pos_x-1, pos_y).get_passable() || field.get_cell(pos_x-1, pos_y).get_has_enemy()
		|| field.get_cell(pos_x-1, pos_y).get_has_object() || seePlayer(player))
		{
			//std::cout << "Change dir to right" << '\n';
			move_dir = Right;
			return;
		}
		//std::cout << "GO LEFT";
		field.get_cell(pos_x, pos_y).clear_enemy();
		//field.get_cell(pos_x, pos_y).set_passable(true);
		//field.get_cell(pos_x, pos_y).set_display('*');
		field.get_cell(pos_x-1, pos_y).set_enemy(*this);
		//pos_x--;
		//field.get_cell(pos_x, pos_y).set_passable(false);
}

void EnemyBoss::move_right(Player& player, Field& field)
{
	if(!field.get_cell(pos_x+1, pos_y).get_passable() || field.get_cell(pos_x+1, pos_y).get_has_enemy()
		|| field.get_cell(pos_x+1, pos_y).get_has_object() || seePlayer(player))
		{
			//std::cout << "Change dir to left" << '\n';
			move_dir = Left;
			return;
		}
		//std::cout << "GO RIGHT";
		field.get_cell(pos_x, pos_y).clear_enemy();
		//field.get_cell(pos_x, pos_y).set_passable(true);
		field.get_cell(pos_x+1, pos_y).set_enemy(*this);
		//pos_x++;
		//field.get_cell(pos_x, pos_y).set_passable(false);	
}

void EnemyBoss::move_up(Player& player, Field& field)
{
	if(!field.get_cell(pos_x, pos_y-1).get_passable() || field.get_cell(pos_x, pos_y-1).get_has_enemy()
		|| field.get_cell(pos_x, pos_y-1).get_has_object() || seePlayer(player))
		{
			//std::cout << "Change dir to left" << '\n';
			move_dir = Down;
			return;
		}
		//std::cout << "GO UP";
		field.get_cell(pos_x, pos_y).clear_enemy();
		//field.get_cell(pos_x, pos_y).set_passable(true);
		field.get_cell(pos_x, pos_y-1).set_enemy(*this);
		//pos_y--;
		//ield.get_cell(pos_x, pos_y).set_passable(false);		
}

void EnemyBoss::move_down(Player& player, Field& field)
{
	if(!field.get_cell(pos_x, pos_y+1).get_passable() || field.get_cell(pos_x, pos_y+1).get_has_enemy()
		|| field.get_cell(pos_x, pos_y+1).get_has_object() || seePlayer(player))
		{
			//std::cout << "Change dir to left" << '\n';
			move_dir = Up;
			return;
		}
		//std::cout << "GO DOWN";
		field.get_cell(pos_x, pos_y).clear_enemy();
		//field.get_cell(pos_x, pos_y).set_passable(true);
		field.get_cell(pos_x, pos_y+1).set_enemy(*this);
		//pos_y++;
		//field.get_cell(pos_x, pos_y).set_passable(false);		
}

void EnemyBoss::move(Player& player, Field& field)
{
	if(seePlayer(player))
		return;
	if(count_of_move == 4)
		count_of_move =0;
	if(count_of_move == 0)
		move_right(player, field);
	else if(count_of_move == 1)
		move_down(player, field);
	else if(count_of_move == 2)
		move_left(player, field);
	else if(count_of_move == 3)
		move_up(player, field);
	count_of_move++;

	Logger::getGlobal().display(*this, "Boss is moving");
}

void EnemyBoss::initView()
{
	cv = new CellObjectView('$', *this);
}


int EnemyBoss::get_pos_x() const { return pos_x; }

int EnemyBoss::get_pos_y() const { return pos_y; }

void EnemyBoss::set_pos_x(int pos) { pos_x = pos; }

void EnemyBoss::set_pos_y(int pos) { pos_y = pos; }


int EnemyBoss::get_health() const { return health; }

void EnemyBoss::set_health(int health) 
{ 
	this->health = health; 
}

int EnemyBoss::get_damage() const { return damage; }

void EnemyBoss::set_damage() {}
