#include "../headers/enemyMove.h"
#include "../headers/cell.h"
#include "../headers/field.h"
#include "../headers/logger.h"

EnemyMove::EnemyMove()
{
	initView();
}

bool EnemyMove::seePlayer(Player& player)
{
	if(std::abs(player.get_posx()-pos_x) <=range && std::abs(player.get_posy()-pos_y) <= range)
		return true;
	return false;
}

void::EnemyMove::init_fight(Player& player, Field& field)
{
	if(seePlayer(player))
	{
		//std::cout << player.get_health() << '\n';
		player.set_health(player.get_health()-damage);
		Logger::getGlobal().display(player, "Player took damage from Move");
	}
}

void EnemyMove::check_for_death(Field& field, std::vector <Enemy*>& enemies, int i)
{
	if(health <=0)
	{
		field.get_cell(pos_x, pos_y).clear_enemy();
		field.get_cell(pos_x, pos_y).set_passable(true);
		enemies.erase(enemies.begin() + i);
	}
}

void EnemyMove::move_left(Player& player, Field& field)
{
	if(pos_x <= 0
		|| !field.get_cell(pos_x-1, pos_y).get_passable() || field.get_cell(pos_x-1, pos_y).get_has_enemy()
		|| field.get_cell(pos_x-1, pos_y).get_has_object() || seePlayer(player) || field.get_cell(pos_x-1, pos_y).get_exit())
		{
			//std::cout << "Change dir to right" << '\n';
			move_dir = Right;
			return;
		}
		//std::cout << "GO LEFT";
		field.get_cell(pos_x, pos_y).clear_enemy();
		//field.get_cell(pos_x, pos_y).set_passable(true);
		field.get_cell(pos_x-1, pos_y).set_enemy(*this);
		//pos_x--;
		//field.get_cell(pos_x, pos_y).set_passable(false);
}

void EnemyMove::move_right(Player& player, Field& field)
{
	if(pos_x >= field.get_size_x()-1
		|| !field.get_cell(pos_x+1, pos_y).get_passable() || field.get_cell(pos_x+1, pos_y).get_has_enemy()
		|| field.get_cell(pos_x+1, pos_y).get_has_object() || seePlayer(player) || field.get_cell(pos_x+1, pos_y).get_exit())
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

void EnemyMove::move_up(Player& player, Field& field)
{
	if(pos_y <= 0
		|| !field.get_cell(pos_x, pos_y-1).get_passable() || field.get_cell(pos_x, pos_y-1).get_has_enemy()
		|| field.get_cell(pos_x, pos_y-1).get_has_object() || seePlayer(player) || field.get_cell(pos_x, pos_y-1).get_exit())
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
		//field.get_cell(pos_x, pos_y).set_passable(false);		
}

void EnemyMove::move_down(Player& player, Field& field)
{
	if(pos_y >= field.get_size_y()-1
		|| !field.get_cell(pos_x, pos_y+1).get_passable() || field.get_cell(pos_x, pos_y+1).get_has_enemy()
		|| field.get_cell(pos_x, pos_y+1).get_has_object() || seePlayer(player) || field.get_cell(pos_x, pos_y+1).get_exit())
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

void EnemyMove::move(Player& player, Field& field)
{
	if(count_of_move%5 == 0)
	{
		std::mt19937 generator;
    	std::random_device rd;
    	generator.seed(rd());
    	std::uniform_int_distribution<> direction(0, 3);
		move_dir = (dir)direction(generator);
		//std::cout << move_dir << std::endl;
	}
	if(count_of_move%20 == 0)
		count_of_move = 0;

	//std::cout << move_dir << '\n';
	if(move_dir == Left)
		move_left(player, field);
	else if(move_dir == Right)
		move_right(player, field);
	else if(move_dir == Up)
		move_up(player, field);
	else if(move_dir == Down)
		move_down(player, field);
	count_of_move++;
	
	Logger::getGlobal().display(*this, "EnemyMove is moving");
}

void EnemyMove::initView()
{
	cv = new CellObjectView('%', *this);
}


int EnemyMove::get_pos_x() const { return pos_x; }

int EnemyMove::get_pos_y() const { return pos_y; }

void EnemyMove::set_pos_x(int pos) { pos_x = pos; }

void EnemyMove::set_pos_y(int pos) { pos_y = pos;}

int EnemyMove::get_health() const { return health; }

void EnemyMove::set_health(int health) { this->health = health; }

int EnemyMove::get_damage() const { return damage; }

void EnemyMove::set_damage() { ; }