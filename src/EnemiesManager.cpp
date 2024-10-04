#include <fstream>
#include "raylib.h"
#include "EnemyBlock.hpp"
#include "EnemiesManager.hpp"
#include "global_resources.hpp"

EnemiesManager::EnemiesManager ()
{
	reset();
	set_difficulty (MEDIUM);
	set_gameMode (ARCADE);
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
	enemies.clear();
	EBS.nextSpawnTime = 3;
}

void EnemiesManager::update (float dt)
{
	spawn_EnemyBlock ();
	enemies.remove_if ([] (const std::unique_ptr<Enemy>& enemy) {return enemy->life_has_ended();});
	for (const std::unique_ptr<Enemy>& enemy : enemies) {enemy->update(dt);}
}

void EnemiesManager::draw ()
{
	for (const std::unique_ptr<Enemy>& enemy : enemies) {enemy->draw();}
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
		initialPos = {(float)random_number (-CURRENT_SCREEN_WIDTH/2, CURRENT_SCREEN_WIDTH/2), -CURRENT_SCREEN_HEIGHT/2.0f - 250};
		break;
		case 2: // down
		initialPos = {(float)random_number (-CURRENT_SCREEN_WIDTH/2, CURRENT_SCREEN_WIDTH/2), CURRENT_SCREEN_WIDTH/2.0f + 250};
		break;
		case 3: // left
		initialPos = {-CURRENT_SCREEN_WIDTH/2.0f - 250, (float)random_number (-CURRENT_SCREEN_HEIGHT/2, CURRENT_SCREEN_HEIGHT/2)};
		break;
		case 4: // right
		initialPos = {CURRENT_SCREEN_WIDTH/2.0f + 250, (float)random_number (-CURRENT_SCREEN_HEIGHT/2, CURRENT_SCREEN_HEIGHT/2.0f)};
		break;
	}
	
	Vector2 maxVelocity = {(float)random_number (EBS.maxVelocityRange), (float)random_number (EBS.maxVelocityRange)};
	Vector2 accForce = {(float)random_number (EBS.maxForceRange), (float)random_number (EBS.maxForceRange)};
	float mass = width*height*EnemyBlock::DENSITY_OF_BLOCKS;
	
	/*preserve balance of the game: */
	if (accForce.x/mass > 3650.0f){
		accForce.x = 3650.0f*mass;
		if (abs (initialPos.x > CURRENT_SCREEN_WIDTH/2.0f)){
			initialPos.x *= 1.5f;
		}
		if (abs (initialPos.y > CURRENT_SCREEN_HEIGHT/2.0f)){
			initialPos.y *= 1.5f;
		}
	}
	if (accForce.y/mass > 3650.0f) {accForce.y = 3650.0f*mass;}
	
	int lifespan = random_number (EBS.lifespanRange);
	
	enemies.push_front (std::make_unique <EnemyBlock> (maxVelocity, accForce, mass, initialPos, lifespan, width, height));
	EBS.nextSpawnTime += random_number (EBS.spawnTimeRange);
}

void EnemiesManager::set_difficulty (Difficulty newDifficulty)
{
	currentDifficulty = newDifficulty;
	update_EnemyBlock_settings ();
}

void EnemiesManager::set_gameMode (GameMode newGameMode)
{
	currentGameMode = newGameMode;
	update_EnemyBlock_settings ();
}


void EnemiesManager::update_EnemyBlock_settings ()
{
	switch (currentDifficulty)
	{
		case EASY:
			EBS.maxCount			= 4;
			EBS.widthRange			= {37, 115};
			EBS.heightRange			= {37, 115};
			EBS.maxVelocityRange	= {800, 1200};
			EBS.maxForceRange		= {2204, 3000};
			EBS.lifespanRange		= {5, 15};
			EBS.spawnTimeRange		= {3, 5};
			break;
		
		case MEDIUM:
			EBS.maxCount			= 4;
			EBS.widthRange			= {37, 130};
			EBS.heightRange			= {37, 130};
			EBS.maxVelocityRange	= {800, 1200};
			EBS.maxForceRange		= {2204, 3200};
			EBS.lifespanRange		= {7, 17};
			EBS.spawnTimeRange		= {3, 4};
			break;
		
		case HARD:
			EBS.maxCount			= 5;
			EBS.widthRange			= {25, 120};
			EBS.heightRange			= {25, 120};
			EBS.maxVelocityRange	= {750, 1150};
			EBS.maxForceRange		= {2204, 2700};
			EBS.lifespanRange		= {4, 15};
			EBS.spawnTimeRange		= {2, 4};
			break;
		
		case INSANE:
			EBS.maxCount			= 5;
			EBS.widthRange			= {25, 55};
			EBS.heightRange			= {25, 55};
			EBS.maxVelocityRange	= {800, 1150};
			EBS.maxForceRange		= {2204, 2700};
			EBS.lifespanRange		= {4, 15};
			EBS.spawnTimeRange		= {2, 3};
			break;
	}
	
	if (currentGameMode == FRENZY){
		EBS.spawnTimeRange		= {0, 0};
	}
}

void EnemiesManager::log_info (int logTime, bool useDefaultLogFile, const char* alternativeFile)
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
	for (const std::unique_ptr<Enemy>& enemy : enemies){
		logFile << '[' << i << ']' << " => " << enemy.get() << ", ";
		i++;
	}

	logFile << Logger::LINE_BREAK;
	
	logFile.close();
}
