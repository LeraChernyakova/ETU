#include "/home/greenjoker/GAME_PROJ/headers/binds/bindPlayer.h"

BindPlayer::BindPlayer(Player* _player, Field* _field)
{
	player = _player; field = _field;
}

Player& BindPlayer::get_player()
{
	return *player;
}

void BindPlayer::set_player(Player* player)
{
	this->player = player;
}

void BindPlayer::set_field(Field* field)
{
	this->field = field;
}



