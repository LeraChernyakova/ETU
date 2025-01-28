#include "SFML/Graphics.hpp"
#include "../headers/game.h"
#include "../headers/exitCond.h"
#include "game.cpp"
#include "exitCond.cpp"
#include "playerDeathCond.cpp"
int main()
{

    Game <ExitCond<1>, DeathCond<0>, 2>game;
    game.onStart();
    game.get_winCond().setField(game.get_field());
    game.get_winCond().setPlayer(game.get_player());
    game.get_winCond().setEnemies(game.get_enemies());
    game.get_lossCond().setPlayer(game.get_player());
    game.Update();
    
}
