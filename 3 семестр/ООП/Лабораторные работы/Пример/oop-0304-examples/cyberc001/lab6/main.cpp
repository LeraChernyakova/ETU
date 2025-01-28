#include "game.h"

#include "rule/exit_condition.h"
#include "rule/player_death_condition.h"

#include "input/key_bind_manager.h"

#include "save/class_creator.h"

int main()
{
	class_creator::init();

	exit_condition win_cond;
	player_death_condition lose_cond;

	std::ifstream binds_in;
	binds_in.open("config_bind");
	key_bind_manager::init(binds_in);

	game maingame(2, win_cond, lose_cond);
	maingame.init();
	win_cond.setGame(&maingame);
	lose_cond.setGame(&maingame);
	maingame.run();
}
