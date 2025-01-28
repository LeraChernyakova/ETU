#ifndef SENTINEL_H
#define SENTINEL_H

#include "../enemy.h"
#include "../../actions/action_shoot_ballistic.h"

class sentinel : public enemy
{
	public:

	sentinel();

	// Properties
	const char* getName() const;

	// Serialization
	virtual std::string getClassName();
};


#endif
