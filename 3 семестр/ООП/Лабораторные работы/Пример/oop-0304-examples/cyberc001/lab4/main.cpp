#include "game.h"
#include "game.cpp"

#include "rule/exit_condition.h"
#include "rule/player_death_condition.h"

int main()
{
	exit_condition win_cond;
	player_death_condition lose_cond;

	game<2> maingame(win_cond, lose_cond);
	maingame.init();
	win_cond.setPlayer(maingame.getMainPlayer());
	lose_cond.setPlayer(maingame.getMainPlayer());
	maingame.run();
}
