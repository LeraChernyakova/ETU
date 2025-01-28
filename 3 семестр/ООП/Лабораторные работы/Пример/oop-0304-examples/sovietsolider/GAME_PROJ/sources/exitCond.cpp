#include "../headers/exitCond.h"
#include "../headers/cell.h"

template<int enemiesToWin>
bool ExitCond<enemiesToWin>::isDone()
{
	return field->get_cell(player->get_posx(), player->get_posy()).get_exit() && (max_enemies_size-enemies->size()) >= enemiesToWin;
}

template<int enemiesToWin>
void ExitCond<enemiesToWin>::setEnemies(std::vector<Enemy*>& enemies)
{
	this->enemies = &enemies;
	max_enemies_size = enemies.size();
}

template<int enemiesToWin>
void ExitCond<enemiesToWin>::setPlayer(Player& player)
{
	this->player = &player;
}

template<int enemiesToWin>
void ExitCond<enemiesToWin>::setField(Field& field)
{
	this->field = &field;
}