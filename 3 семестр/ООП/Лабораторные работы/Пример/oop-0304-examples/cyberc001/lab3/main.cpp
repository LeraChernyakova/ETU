#include <fstream>
#include <iostream>

#include "field.h"
#include "field_view.h"

#include "actors/player.h"
#include "actors/enemies/acolyte.h"

#include "logger/observer_actor.h"
#include "logger/global_logger.h"

#include "logger/fstream_wrapper.h"

void clear_tscreen()
{
	std::cout << "\033[H\033[J";
}

int main()
{
	ostream_wrapper coutw(std::cout);

	std::ofstream fd_out;
	fstream_wrapper fdw_out(fd_out, "game_out");
	global_logger::init_loggers({coutw, dynamic_cast<ostream_wrapper&>(fdw_out)});

	field f(12, 12);
	field_view fv(f);

	cell_entrance* ce = f.generate_entrance_exit(5);

	observer_actor mainplr_obs({coutw, dynamic_cast<ostream_wrapper&>(fdw_out)});
	player* mainplr = new player();
	{
		mainplr_obs.setActor(*mainplr);

		mainplr->setMaxHealth(30);
		mainplr->setHealth(30);
		ce->set_object(mainplr);
	}

	size_t x, y;
	do{
		x = std::rand() % 12; y = std::rand() % 12;
	} while(!f.get_cell(x, y).is_passable() || f.get_cell(x, y).has_object() );

	observer_actor a1_observer({coutw, dynamic_cast<ostream_wrapper&>(fdw_out)});
	{
		acolyte* a = new acolyte();
		a1_observer.setActor(*a);
		a->setTeamID(1);
		f.get_cell(x, y).set_object(a);
	}

	clear_tscreen();
	fv.display();
	getc(stdin);
	while(1){
		clear_tscreen();
		f.tickActors();
		fv.display();
		getc(stdin);
	}

	delete mainplr;
}
