#include "Exit.h"

void Exit::addGood(Player& player) {}

void Exit::reaction(Player& player) {
	player.setWinner();
}