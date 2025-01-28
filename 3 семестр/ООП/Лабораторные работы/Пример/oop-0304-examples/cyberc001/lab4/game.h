#ifndef GAME_H
#define GAME_H

#include "actors/enemies/acolyte.h"

#include "logger/ostream_wrapper.h"
#include "logger/observer_actor.h"

#include "rule/actor_spawner.h"
#include "rule/actor_spawner.cpp"
#include "rule/game_condition.h"

#include "actors/player.h"

#include "field.h"
#include "field_view.h"

template <size_t difficulty>
class game
{
	private:

	field* mainfield;
	field_view* mainfield_view;

	player* mainplr = nullptr;

	static std::vector<actor_spawner_func> enemy_spawn_funcs;
	std::vector<actor*> actors_spawned;

	game_condition& win_cond;
	game_condition& lose_cond;


	public:

	// game management
	game(game_condition& win_cond, game_condition& lose_cond);
	~game();

	void init();
	void run();

	// public getters
	const player* getMainPlayer();
};

#endif
