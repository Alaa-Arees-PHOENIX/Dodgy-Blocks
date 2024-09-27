#include <iostream>
#include <fstream>
#include "raylib.h"
#include "Enemy.hpp"
#include "global_resources.hpp"

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

void Enemy::log_info (int logTime, bool useDefaultLogFile, const char* alternativeFile)
{
	std::ofstream logFile;
	if (useDefaultLogFile){
		logFile.open("log/Enemy_log.txt", std::ios_base::app);
	}
	else {logFile.open (alternativeFile, std::ios_base::app);}
	
	logFile << Logger::LINE_BREAK;
	
	logFile << "Enemy instance, logged at " << logTime << '\n';
	logFile << "address: " << this << '\n';
	logFile << "spawn time: " << SPAWN_TIME << '\n';
	logFile << "death time: " << DEATH_TIME << '\n';
	
	logFile << Logger::LINE_BREAK;
	
	logFile.close();
}
