#include "acolyte.h"

#include "../../save/class_creator_inserter.h"

acolyte::acolyte()
{
	initView();

	max_ap = 8;
	detection_dist = 35;

	setHealth(40);
	setMaxHealth(50);
	setDamageThreshold(3);
	setDamageResistance(0.2);

	atk_action = new action_shoot_ballistic(6, 3, 10);
	mv_action = new action_move(3.0);
}

const char* acolyte::getName() const { return "Acolyte"; }

// Serialization
static default_constructor_func dcf = [](){ return new acolyte(); };
static class_creator_inserter cci("acolyte", &dcf);
std::string acolyte::getClassName(){ return "acolyte"; }
