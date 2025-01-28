#include "stalkerbot.h"

stalkerbot::stalkerbot()
{
	initView();

	max_ap = 6;
	detection_dist = 20;

	setMaxHealth(80);
	setDamageThreshold(6);
	setDamageResistance(0.2);

	atk_action = new action_shoot_ballistic(6, 5, 3);
	mv_action = new action_move(0.8);
}
