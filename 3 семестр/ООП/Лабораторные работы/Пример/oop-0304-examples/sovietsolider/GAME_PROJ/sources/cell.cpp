#include "../headers/cell.h"

Cell::Cell()
{
	cv = new CellView('*', *this);
}


void Cell::set_display(char setter) { display = setter; }

CellView& Cell::get_display() { return *cv; }

void Cell::set_passable(bool state) { passable = state; }

bool Cell::get_passable() { return passable; }

void Cell::set_exit(bool state) { exit = state; }

bool Cell::get_exit() { return exit; }

void Cell::set_entrance(bool state) { entrance = state; }

bool Cell::get_entrance() { return entrance; }

void Cell::set_object(Object& object) 
{ 
	stored_object = &object; 
	object.set_pos_x(x);
	object.set_pos_y(y);
}

CellObject& Cell::get_object() { return *stored_object; }

bool Cell::get_has_object() { return stored_object; }

int Cell::get_x() { return x; }

int Cell::get_y() { return y; }

void Cell::set_x(int x) { this->x = x; }

void Cell::set_y(int y) { this->y = y; }

void Cell::set_player(Player& player) { this->player = &player; }

CellObject& Cell::get_player() { return *player; }

void Cell::set_enemy(Enemy& enemy) 
{ 
	this->enemy = &enemy;
	enemy.set_pos_x(x);
	enemy.set_pos_y(y);
	passable = false;
}

CellObject& Cell::get_enemy() { return *enemy; }

void Cell::clear_object() { stored_object = nullptr; }

void Cell::clear_enemy() 
{ 
	enemy = nullptr; 
	passable = true;
}

void Cell::clear_player() { player = nullptr; }

bool Cell::get_has_enemy() { return enemy; }

bool Cell::get_has_player() { return player; }

bool Cell::isWall() { return wall; }

void Cell::set_isWall(bool state) { wall = state; }

