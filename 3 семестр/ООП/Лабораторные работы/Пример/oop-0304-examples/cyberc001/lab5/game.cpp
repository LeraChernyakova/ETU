#include "game.h"

#include <fstream>
#include <iostream>

#include "ui/game_view.h"
#include "ui/ui_menu_player_actions.h"

#include "actors/enemies/acolyte.h"

#include "logger/global_logger.h"
#include "logger/fstream_wrapper.h"

#include "input/key_bind_manager.h"

#include "actors/items/armor_item.h"
#include "actors/items/health_item.h"
#include "actors/items/weapon_item.h"

std::vector<actor_spawner_func> game::enemy_spawn_funcs;


game::game(size_t difficulty, game_condition& win_cond, game_condition& lose_cond)
	: difficulty(difficulty), win_cond(win_cond), lose_cond(lose_cond) {}


void game::init()
{
	mainfield = new field(30, 30);
	mainfield_view = new field_view(*mainfield);

	cell_entrance* ce = mainfield->generate_entrance_exit(difficulty * 8);

	mainplr = new player();
	{
		mainplr->setMaxHealth(30);
		mainplr->setHealth(30 / ((double)difficulty / 2));
		mainplr->setTeamID(10);
		mainplr->setMaxAP(8);
		mainplr->setAP(8);
		ce->set_object(mainplr);

		mainplr->addItemToInventory(new health_item(15));
		mainplr->addItemToInventory(new weapon_item(14, 1.));
		mainplr->addItemToInventory(new armor_item(2, 0.2));
	}

	{
		enemy_spawn_funcs.push_back([](const cell& pc){return new acolyte();});
		actor_spawner<enemy_spawn_funcs> enemy_spawner;
		const std::vector<actor*>& enemies_spawned = enemy_spawner.doSpawn(*mainfield, difficulty);
		actors_spawned.insert(actors_spawned.end(), enemies_spawned.begin(), enemies_spawned.end());
	}
}


void game::run()
{
	game_view main_ui(*this);
	input_manager inmngr;

	ui_menu_player_actions menu_actions(0, &mainplr->getMoveAction());

	ostream_wrapper coutw(std::cout);

	std::ofstream fd_out;
	fstream_wrapper fdw_out(fd_out, "game_out");
	ostream_wrapper log_bufw(main_ui.getLogBuffer());

	global_logger::init_loggers(GLOGGER_LEVEL_UI, {coutw});
	global_logger::init_loggers(GLOGGER_LEVEL_EVENT, {fdw_out, log_bufw});
	observer_actor mainplr_obs({fdw_out, log_bufw});
	mainplr_obs.setActor(*mainplr);

	std::vector<observer_actor*> actors_obs;
	for(auto i = actors_spawned.begin(); i != actors_spawned.end(); ++i)
	{
		observer_actor* obsa = new observer_actor({fdw_out, log_bufw});
		obsa->setActor(**i);
		actors_obs.push_back(obsa);
	}

	main_ui.refresh();

	int first_iter = 1;
	while(1){
		if(!first_iter)
			mainfield->tickActors();
		else
			first_iter = 0;

		if(win_cond.isMet()){
			global_logger::message(GLOGGER_LEVEL_EVENT, "You won!");
			break;
		}
		if(lose_cond.isMet()){
			global_logger::message(GLOGGER_LEVEL_EVENT, "You lost!");
			break;
		}

		main_ui.refresh();
		menu_actions.execute(main_ui, inmngr);
		main_ui.clearLogBuffer();
	}

	main_ui.refresh();
	for(auto i = actors_obs.begin(); i != actors_obs.end(); ++i)
		delete *i;
}

game::~game()
{
	delete mainplr;
	for(size_t i = 0; i < actors_spawned.size(); ++i)
		delete actors_spawned[i];
}


// public getters

player& game::getMainPlayer() { return *mainplr; }
field& game::getMainField() { return *mainfield; }

field_view& game::getMainFieldView() { return *mainfield_view; }
