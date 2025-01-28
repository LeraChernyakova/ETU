#include <iostream>

#include "field.h"
#include "field_view.h"

#include "actors/player.h"
#include "actors/enemies/acolyte.h"

void clear_tscreen()
{
	std::cout << "\033[H\033[J";
}

int main()
{
	field f(12, 12);
	field_view fv(f);

	cell_entrance* ce = f.generate_entrance_exit(5);
	{
		player* mainplr = new player();
		mainplr->setMaxHealth(30);
		mainplr->setHealth(30);
		ce->set_object(mainplr);
	}

	size_t x, y;
	do{
		x = std::rand() % 12; y = std::rand() % 12;
	} while(!f.get_cell(x, y).is_passable() || f.get_cell(x, y).has_object() );

	{
		acolyte* a = new acolyte();
		a->setTeamID(1);
		f.get_cell(x, y).set_object(a);
	}

	while(1){
		clear_tscreen();
		fv.display();

		getc(stdin);

		f.tickActors();
		getc(stdin);
	}
}
