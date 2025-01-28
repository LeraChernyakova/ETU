#ifndef GAME_H
#define GAME_H

#include "logger/ostream_wrapper.h"
#include "logger/observer_actor.h"

#include "rule/actor_spawner.h"
#include "rule/actor_spawner.cpp"
#include "rule/game_condition.h"

#include "actors/player.h"

#include "input/input_manager.h"

#include "field.h"
#include "field_view.h"

class game_ui;

class game
{
	private:

	field* mainfield;
	field_view* mainfield_view;

	player* mainplr = nullptr;

	static std::vector<actor_spawner_func> enemy_spawn_funcs;
	std::vector<actor*> actors_spawned;

	// game parameters
	size_t difficulty;
	game_condition& win_cond;
	game_condition& lose_cond;

	// observers
	ostream_wrapper* log_bufw;
	observer_actor* mainplr_obs;
	std::vector<observer_actor*> actors_obs;


	public:

	// game management
	game(size_t difficulty, game_condition& win_cond, game_condition& lose_cond);
	~game();

	bool load(std::string fname);
	bool save(std::string fname);

	void init();
	void run();

	// public getters
	player& getMainPlayer();
	field& getMainField();

	field_view& getMainFieldView();
};

#endif
