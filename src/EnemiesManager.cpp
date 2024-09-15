#include <fstream>
#include "raylib.h"
#include "EnemyBlock.hpp"
#include "EnemiesManager.hpp"
#include "global_resources.hpp"

EnemiesManager::EnemiesManager ()
{
	reset();
	set_difficulty (MEDIUM);
	#if defined(DEBUG)
		LOGGER.add_listener (this);
	#endif
}

EnemiesManager::~EnemiesManager ()
{
	#if defined(DEBUG)
		LOGGER.remove_listener (this);
	#endif
}

void EnemiesManager::reset ()
{
	for (auto it = enemies.begin(); it != enemies.end(); it++) {delete *it;}
	enemies.clear();
	EBS.nextSpawnTime = 3;
}

void EnemiesManager::update (float dt)
{
	spawn_EnemyBlock ();
	
	while (!enemies.empty() && (*enemies.begin())->life_has_ended()){
		delete *(enemies.begin());
		enemies.erase (enemies.begin());
	}
	
	for (auto it = enemies.begin(); it != enemies.end(); it++){
		(*it)->update(dt);
	}
}

void EnemiesManager::draw ()
{
	for (auto it = enemies.begin(); it != enemies.end(); it++){
		(*it)->draw();
	}
}

void EnemiesManager::spawn_EnemyBlock ()
{	
	if (TIMER.get_time () < EBS.nextSpawnTime || EnemyBlock::get_instances_count() >= EBS.maxCount) {return;}
	
	float width = (float)random_number (EBS.widthRange);
	float height = (float)random_number (EBS.heightRange);
	
	Vector2 initialPos = {0, 0};
    int whichSideToSpawnFrom = random_number (1, 4);
    switch (whichSideToSpawnFrom)
    {
		case 1: // up
		initialPos = {(float)random_number (-CURRENT_SCREEN_WIDTH/2, CURRENT_SCREEN_WIDTH/2), -CURRENT_SCREEN_HEIGHT/2.0f - 190};
		break;
		case 2: // down
		initialPos = {(float)random_number (-CURRENT_SCREEN_WIDTH/2, CURRENT_SCREEN_WIDTH/2), CURRENT_SCREEN_WIDTH/2.0f + 190};
		break;
		case 3: // left
		initialPos = {-CURRENT_SCREEN_WIDTH/2.0f - 190, (float)random_number (-CURRENT_SCREEN_HEIGHT/2, CURRENT_SCREEN_HEIGHT/2)};
		break;
		case 4: // right
		initialPos = {CURRENT_SCREEN_WIDTH/2.0f + 190, (float)random_number (-CURRENT_SCREEN_HEIGHT/2, CURRENT_SCREEN_HEIGHT/2.0f)};
		break;
	}
	
	Vector2 maxVelocity = {(float)random_number (EBS.maxVelocityRange), (float)random_number (EBS.maxVelocityRange)};
	Vector2 accForce = {(float)random_number (EBS.maxForceRange), (float)random_number (EBS.maxForceRange)};
	float mass = width*height*EnemyBlock::DENSITY_OF_BLOCKS;
	
	int lifespan = random_number (EBS.lifespanRange);
	
	enemies.insert (new EnemyBlock (maxVelocity, accForce, mass, initialPos, lifespan, width, height));
	EBS.nextSpawnTime += random_number (EBS.spawnTimeRange);
}

void EnemiesManager::set_difficulty (Difficulty newDifficulty)
{
	currentDifficulty = newDifficulty;
	update_EnemyBlock_settings ();
}


void EnemiesManager::update_EnemyBlock_settings ()
{
	switch (currentDifficulty)
	{
		case EASY:
			EBS.maxCount			= 4;
			EBS.widthRange			= {37, 111};
			EBS.heightRange			= {37, 111};
			EBS.maxVelocityRange	= {800, 1200};
			EBS.maxForceRange		= {2500, 3550};
			EBS.lifespanRange		= {5, 15};
			EBS.spawnTimeRange		= {3, 5};
			break;
		
		case MEDIUM:
			EBS.maxCount			= 4;
			EBS.widthRange			= {37, 130};
			EBS.heightRange			= {37, 130};
			EBS.maxVelocityRange	= {800, 1300};
			EBS.maxForceRange		= {2500, 3650};
			EBS.lifespanRange		= {7, 17};
			EBS.spawnTimeRange		= {3, 4};
			break;
		
		case HARD:
			EBS.maxCount			= 5;
			EBS.widthRange			= {20, 130};
			EBS.heightRange			= {20, 130};
			EBS.maxVelocityRange	= {750, 1350};
			EBS.maxForceRange		= {2650, 3650};
			EBS.lifespanRange		= {4, 17};
			EBS.spawnTimeRange		= {2, 4};
			break;
		
		case INSANE:
			EBS.maxCount			= 6;
			EBS.widthRange			= {10, 55};
			EBS.heightRange			= {10, 55};
			EBS.maxVelocityRange	= {750, 1350};
			EBS.maxForceRange		= {2650, 3650};
			EBS.lifespanRange		= {4, 17};
			EBS.spawnTimeRange		= {2, 3};
			break;
	}
}

void EnemiesManager::logInfo (int logTime, bool useDefaultLogFile, const char* alternativeFile)
{
	std::ofstream logFile;
	if (useDefaultLogFile){
		logFile.open ("log/EnemiesManager_log.txt", std::ios_base::app);
	}
	else {logFile.open (alternativeFile, std::ios_base::app);}
	
	logFile << Logger::LINE_BREAK;

	logFile << "EnemiesManager instance, logged at: " << logTime << '\n';
	logFile << "game time: " << TIMER.get_time() << '\n';
	logFile << "address: " << this << '\n';
	logFile << "difficulty: " << currentDifficulty << '\n';
	logFile << "EBS max count = " << EBS.maxCount << '\n';
	logFile << "EBS next spawn = " << EBS.nextSpawnTime << '\n';
	logFile << "EBS width range = " << to_string (EBS.widthRange) << '\n';
	logFile << "EBS height range = " << to_string (EBS.heightRange) << '\n';
	logFile << "EBS spawn time range = " << to_string (EBS.spawnTimeRange) << '\n';
	logFile << "EBS max velocity range = " << to_string (EBS.maxVelocityRange) << '\n';
	logFile << "EBS max force range = " << to_string (EBS.maxForceRange) << '\n';
	logFile << "EBS lifespan range = " << to_string (EBS.lifespanRange) << '\n';
	
	int i = 0;
	for (Enemy* enemy : enemies){
		logFile << '[' << i << ']' << enemy << ", ";
		i++;
	}

	logFile << Logger::LINE_BREAK;
	
	logFile.close();
}
