#ifndef ACOLYTE_H
#define ACOLYTE_H

#include "../enemy.h"
#include "../../actions/action_shoot_ballistic.h"

class acolyte : public enemy
{
	public:

	acolyte();

	// Properties
	const char* getName() const;

	// Serialization
	virtual std::string getClassName();
};

#endif
