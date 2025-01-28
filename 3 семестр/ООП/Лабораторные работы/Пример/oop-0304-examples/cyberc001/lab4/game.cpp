#include "game.h"

#include <fstream>
#include <iostream>

#include "actors/enemies/acolyte.h"

#include "logger/global_logger.h"

#include "logger/fstream_wrapper.h"


static void clear_tscreen()
{
	std::cout << "\033[H\033[J";
}


template <size_t difficulty>
std::vector<actor_spawner_func> game<difficulty>::enemy_spawn_funcs;


template <size_t difficulty>
game<difficulty>::game(game_condition& win_cond, game_condition& lose_cond) : win_cond(win_cond), lose_cond(lose_cond)
{}

template <size_t difficulty>
void game<difficulty>::init()
{
	mainfield = new field(15, 15);
	mainfield_view = new field_view(*mainfield);

	cell_entrance* ce = mainfield->generate_entrance_exit(difficulty * 8);

	mainplr = new player();
	{
		mainplr->setMaxHealth(30);
		mainplr->setHealth(30 / ((double)difficulty / 2));
		mainplr->setTeamID(10);
		ce->set_object(mainplr);
	}

	{
		enemy_spawn_funcs.push_back([](const cell& pc){return new acolyte();});
		actor_spawner<enemy_spawn_funcs, difficulty> enemy_spawner;
		const std::vector<actor*>& enemies_spawned = enemy_spawner.doSpawn(*mainfield);
		actors_spawned.insert(actors_spawned.end(), enemies_spawned.begin(), enemies_spawned.end());
	}
}

template <size_t difficulty>
void game<difficulty>::run()
{
	std::ofstream fd_out;
	fstream_wrapper fdw_out(fd_out, "game_out");
	ostream_wrapper coutw(std::cout);

	global_logger::init_loggers({coutw, fdw_out});
	observer_actor mainplr_obs({coutw, fdw_out});
	mainplr_obs.setActor(*mainplr);

	std::vector<observer_actor*> actors_obs;
	for(auto i = actors_spawned.begin(); i != actors_spawned.end(); ++i)
	{
		observer_actor* obsa = new observer_actor({coutw, fdw_out});
		obsa->setActor(**i);
		actors_obs.push_back(obsa);
	}

	clear_tscreen();
	mainfield_view->display();
	getc(stdin);
	while(1){
		//clear_tscreen();
		mainfield->tickActors();
		if(win_cond.isMet()){
			std::cout << "You won!\n";
			break;
		}
		if(lose_cond.isMet()){
			std::cout << "You lost!\n";
			break;
		}
		mainfield_view->display();
		getc(stdin);
	}

	for(auto i = actors_obs.begin(); i != actors_obs.end(); ++i)
		delete *i;
}


template <size_t difficulty>
game<difficulty>::~game()
{
	delete mainplr;
	for(size_t i = 0; i < actors_spawned.size(); ++i)
		delete actors_spawned[i];
}


// public getters
template <size_t difficulty>
const player* game<difficulty>::getMainPlayer() { return mainplr; }
