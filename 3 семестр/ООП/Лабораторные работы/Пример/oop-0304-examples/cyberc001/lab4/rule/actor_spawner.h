#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

#include <functional>
#include <vector>

#include "../actors/actor.h"
#include "../cells/cell.h"

typedef std::function<actor*(const cell& pc)> actor_spawner_func;

template<std::vector<actor_spawner_func>& spawn_funcs, size_t amount>
class actor_spawner
{
	private:

	std::vector<actor*> spawned_actors;


	public:

	const std::vector<actor*>& doSpawn(const field& f);
};

#endif
