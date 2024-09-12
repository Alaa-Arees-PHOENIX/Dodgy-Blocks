#include "raylib.h"
#include "Enemy.hpp"
#include "global_resources.hpp"
#include <iostream>

Enemy::Enemy (int lifespan)
	:	SPAWN_TIME (TIMER.get_time()), DEATH_TIME (TIMER.get_time() + lifespan)
{
	
}

Enemy::~Enemy ()
{
	#if defined(DEBUG)
		std::cerr << "Enemy destroy\n";
	#endif
}

bool Enemy::life_has_ended ()
{
	return  TIMER.get_time () >= DEATH_TIME;
}