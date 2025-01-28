#include "game.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "ui/game_view.h"
#include "ui/ui_menu_player_actions.h"

#include "actors/enemies/acolyte.h"

#include "logger/global_logger.h"
#include "logger/fstream_wrapper.h"

#include "input/key_bind_manager.h"

#include "actors/items/armor_item.h"
#include "actors/items/health_item.h"
#include "actors/items/weapon_item.h"

#include "save/class_creator.h"
#include "save/save_exceptions.h"

std::vector<actor_spawner_func> game::enemy_spawn_funcs;


game::game(size_t difficulty, game_condition& win_cond, game_condition& lose_cond)
	: difficulty(difficulty), win_cond(win_cond), lose_cond(lose_cond) {}


bool game::save(std::string fname)
{
	savestream svs;
	svs.open(fname, std::fstream::out | std::fstream::trunc);
	try{
		mainfield->saveToFile(svs);
	}
	catch (save_error_unexpected_eof& e){
		std::stringstream ss;
		ss << "Can't save the game: " << e.what();
		global_logger::message(GLOGGER_LEVEL_UI, ss.str());
		svs.close();
		return false;
	}
	svs.close();
	return true;
}
bool game::load(std::string fname)
{
	savestream svs;
	svs.open(fname, std::fstream::in);
	field* new_mainfield = nullptr;
	try{
		new_mainfield = (field*)class_creator::loadObject(svs);
	}
	catch (save_error_unexpected_eof& e){
		std::stringstream ss;
		ss << "Can't load the game: " << e.what();
		global_logger::message(GLOGGER_LEVEL_UI, ss.str());
		svs.close();
		return false;
	}
	player* new_mainplr = (player*)new_mainfield->scan_for_object("player");
	svs.close();

	delete mainfield;
	delete mainfield_view;
	delete mainplr;
	for(size_t i = 0; i < actors_spawned.size(); ++i)
		delete actors_spawned[i];
	for(size_t i = 0; i < actors_obs.size(); ++i)
		delete actors_obs[i];
	actors_spawned.clear();
	actors_obs.clear();

	mainfield = new_mainfield;
	mainfield_view = new field_view(*mainfield);
	mainplr = new_mainplr;
	mainplr_obs->setActor(*mainplr);

	std::vector<actor*> spacs = mainfield->scan_for_actors();
	for(auto i = spacs.begin(); i != spacs.end(); ++i){
		if(dynamic_cast<player*>(*i))
			continue;
		actors_spawned.push_back((actor*)*i);
	}

	for(auto i = actors_spawned.begin(); i != actors_spawned.end(); ++i)
	{
		observer_actor* obsa = new observer_actor({*log_bufw});
		obsa->setActor(**i);
		actors_obs.push_back(obsa);
	}

	return true;
}


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

	log_bufw = new ostream_wrapper(main_ui.getLogBuffer());

	global_logger::init_loggers(GLOGGER_LEVEL_UI, {coutw});
	global_logger::init_loggers(GLOGGER_LEVEL_EVENT, {*log_bufw});
	mainplr_obs = new observer_actor({*log_bufw});
	mainplr_obs->setActor(*mainplr);

	for(auto i = actors_spawned.begin(); i != actors_spawned.end(); ++i)
	{
		observer_actor* obsa = new observer_actor({*log_bufw});
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
}

game::~game()
{
	delete mainplr;
	for(size_t i = 0; i < actors_spawned.size(); ++i)
		delete actors_spawned[i];
	for(auto i = actors_obs.begin(); i != actors_obs.end(); ++i)
		delete *i;
}


// public getters

player& game::getMainPlayer() { return *mainplr; }
field& game::getMainField() { return *mainfield; }

field_view& game::getMainFieldView() { return *mainfield_view; }
