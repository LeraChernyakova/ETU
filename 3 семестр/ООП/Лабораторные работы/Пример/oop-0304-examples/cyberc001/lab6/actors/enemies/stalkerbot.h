#ifndef STALKERBOT_H
#define STALKERBOT_H

#include "../enemy.h"
#include "../../actions/action_shoot_ballistic.h"

class stalkerbot : public enemy
{
	public:

	stalkerbot();

	// Properties
	const char* getName() const;

	// Serialization
	virtual std::string getClassName();
};

#endif
