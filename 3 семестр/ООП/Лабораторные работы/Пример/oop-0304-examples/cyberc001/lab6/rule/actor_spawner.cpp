#include "actor_spawner.h"

#include <cstdlib>

#include "../field.h"

template<std::vector<actor_spawner_func>& spawn_funcs>
const std::vector<actor*>& actor_spawner<spawn_funcs>::doSpawn(const field& f, size_t amount)
{
	size_t valid_cells = 0;
	for(size_t y = 0; y < f.get_h(); ++y)
		for(size_t x = 0; x < f.get_w(); ++x)
			if(f.get_cell(x, y).is_passable() && !f.get_cell(x, y).has_object())
				++valid_cells;

	size_t real_amount = std::min(amount, valid_cells);
	for(size_t i = 0; i < real_amount; ++i)
	{
		size_t x, y;
		do{
			x = std::rand() % f.get_w();
			y = std::rand() % f.get_h();
		} while(!f.get_cell(x, y).is_passable() || f.get_cell(x, y).has_object());
		actor* a = spawn_funcs[std::rand() % spawn_funcs.size()](f.get_cell(x, y));
		spawned_actors.push_back(a);
		f.get_cell(x, y).set_object(a);
	}

	return spawned_actors;
}
