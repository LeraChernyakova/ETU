#include "../headers/player.h"
#include "../headers/field.h"
#include "../headers/logger.h"

Player::Player()
{
	initView();
}

void Player::move_left(Field& field)
{
	if(get_posx() != 0 && field.get_cell(get_posx()-1, get_posy()).get_passable())
	{
		//std::cout << "GO LEFT";
		field.get_cell(get_posx(), get_posy()).clear_player();
		field.get_cell(get_posx()-1, get_posy()).set_player(*this);
		set_posx(get_posx()-1);
		Logger::getGlobal().display(*this, "PlayerMove");
	}	
}

void Player::move_right(Field& field)
{
	if(get_posx() != field.get_size_x()-1 && field.get_cell(get_posx()+1, get_posy()).get_passable())
	{
		//std::cout << "GO RIGHT";
		field.get_cell(get_posx(), get_posy()).clear_player();
		field.get_cell(get_posx()+1, get_posy()).set_player(*this);
		set_posx(get_posx()+1);
		Logger::getGlobal().display(*this, "PlayerMove");
	}	
}

void Player::move_up(Field& field)
{
	if(get_posy() != 0 && field.get_cell(get_posx(), get_posy()-1).get_passable())
	{
		//std::cout << "GO UP";
		field.get_cell(get_posx(), get_posy()).clear_player();
		field.get_cell(get_posx(), get_posy()-1).set_player(*this);
		set_posy(get_posy()-1);
		std::cout << get_posy();
		Logger::getGlobal().display(*this, "PlayerMove");
	}	
}

void Player::move_down(Field& field)
{
	if(get_posy() != field.get_size_y()-1 && field.get_cell(get_posx(), get_posy()+1).get_passable())
	{
		//std::cout << "GO DOWN";
		field.get_cell(get_posx(), get_posy()).clear_player();
		field.get_cell(get_posx(), get_posy()+1).set_player(*this);
		set_posy(get_posy()+1);
		std::cout << get_posy();
		Logger::getGlobal().display(*this, "PlayerMove");
	}
}

bool Player::see_enemy(Enemy* enemy, Field field)
{
	if(std::abs(enemy->get_pos_x()-pos_x) <=range && std::abs(enemy->get_pos_y()-pos_y) <= range
	&& field.get_cell(enemy->get_pos_x(), enemy->get_pos_y()).get_has_enemy())
		return true;
	return false;
}

void Player::init_fight(Enemy* enemy, Field field)
{
	if(see_enemy(enemy, field))
	{
		//std::cout << "IM Player INIT" << std::endl;
		enemy->set_health(enemy->get_health()-damage);
		Logger::getGlobal().display(*enemy, "Enemy took damage from player");
	}
}

bool Player::check_for_death(Field& field)
{
	if(health<0)
	{
		field.get_cell(pos_x, pos_y).set_passable(true);
		return true;
	}
	else
		return false;
}

void Player::initView()
{
	cv = new CellObjectView('3', *this);
}


int Player::get_posx() const { return pos_x; }

int Player::get_posy() const { return pos_y; }

void Player::set_posx(int pos_x) { this->pos_x = pos_x; }

void Player::set_posy(int pos_y) { this->pos_y = pos_y; }

float Player::get_damage() const { return damage; }

float Player::get_health() const { return health; }

void Player::set_damage(float damage) { this->damage = damage; }

void Player::set_health(float health) 
{ 
	if(health <= 100)
		this->health = health; 
}

int Player::get_range() const { return range; }

void Player::set_range(int range) { this->range = range; }  


std::ostream& operator<<(std::ostream& os, const Player& actor)
{
	os  << " health: " << actor.get_health()
		<< " damage: " << actor.get_damage()
		<< " PosX: " << actor.get_posx()
		<< " PosY: " << actor.get_posy();
	return os;
}


