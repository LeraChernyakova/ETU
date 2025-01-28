#ifndef BINDPLAYER_H
#define BINDPLAYER_H
#include "bind.h"
#include "../player.h"

class BindPlayer : public Bind
{
	protected:
		Player* player;
		Field* field;
		
	public:
		BindPlayer(Player* _player, Field* _field);
		Player& get_player();
		void set_player(Player* player);
		void set_field(Field* field);
		
};

#endif