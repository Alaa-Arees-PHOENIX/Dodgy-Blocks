#include <fstream>
#include "Logger.hpp"
#include "raylib.h"

Logger::Logger ()
{
	timeSinceGameLaunch = 0;
	
	// overwrite old logs:
	std::ofstream f;
	f.open ("log/MotiveCreature_log.txt", std::ios_base::out);
	f.close();
	f.open ("log/Enemy_log.txt", std::ios_base::out);
	f.close();
	f.open ("log/Player_log.txt", std::ios_base::out);
	f.close();
	f.open ("log/EnemyBlock_log.txt", std::ios_base::out);
	f.close();
	f.open ("log/EnemiesManager_log.txt", std::ios_base::out);
	f.close();
	f.open ("log/FlyingBall_log.txt", std::ios_base::out);
	f.close();
}

void Logger::add_listener (Listener* listener)
{
	listeners.push_front (listener);
}

void Logger::remove_listener (Listener* listener)
{
	listeners.remove (listener);
}

void Logger::update (float dt)
{
	timeSinceGameLaunch += dt;
	if (IsKeyPressed (KEY_L)) {log_all();}
}

void Logger::log_all ()
{
	for (Listener* listener : listeners){
		listener->log_info((int)timeSinceGameLaunch);
	}
}