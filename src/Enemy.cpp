#include "raylib.h"
#include "Enemy.hpp"
#include "global_resources.hpp"

Enemy::Enemy (int lifespan)
	:	SPAWN_TIME (TIMER.get_time()), DEATH_TIME (TIMER.get_time() + lifespan)
{
	
}

Enemy::~Enemy () {}

bool Enemy::life_has_ended ()
{
	return  TIMER.get_time () >= DEATH_TIME;
}