#include "raylib.h"
#include "EnemyBlock.hpp"
#include "EnemiesManager.hpp"
#include "global_resources.hpp"

EnemiesManager::EnemiesManager ()
{
	reset();
	currentDifficulty = MEDIUM;
}

void EnemiesManager::reset ()
{
	for (auto it = enemies.begin(); it != enemies.end(); it++) {delete *it;}
	enemies.clear();
	EnemyBlock_settings::nextSpawnTime = 3;
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
	/* this function is specific to EnemyBlock */
	using namespace EnemyBlock_settings;
	
	if (TIMER.get_time () < nextSpawnTime || EnemyBlock::get_instances_count() >= maxCount) {return;}
	
	float width = (float)random_number (widthRange);
	float height = (float)random_number (heightRange);
	
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
	
	Vector2 maxVelocity = {(float)random_number (maxVelocityRange), (float)random_number (maxVelocityRange)};
	Vector2 accForce = {(float)random_number (maxForceRange), (float)random_number (maxForceRange)};
	float mass = width*height*EnemyBlock::DENSITY_OF_BLOCKS;
	
	int lifespan = random_number (lifespanRange);
	
	enemies.insert (new EnemyBlock (maxVelocity, accForce, mass, initialPos, lifespan, width, height));
	nextSpawnTime += random_number (spawnTimeRange);
}

void EnemiesManager::set_difficulty (Difficulty newDifficulty)
{
	currentDifficulty = newDifficulty;
	update_EnemyBlock_settings ();
}


void EnemiesManager::update_EnemyBlock_settings ()
{
	/* this function is specific to EnemyBlock */
	using namespace EnemyBlock_settings;
	
	switch (currentDifficulty)
	{
		case EASY:
			maxCount			= 4;
			widthRange			= {37, 111};
			heightRange			= {37, 111};
			maxVelocityRange	= {800, 1200};
			maxForceRange		= {2500, 3550};
			lifespanRange		= {5, 15};
			spawnTimeRange		= {3, 5};
			break;
		
		case MEDIUM:
			maxCount			= 4;
			widthRange			= {37, 130};
			heightRange			= {37, 130};
			maxVelocityRange	= {800, 1300};
			maxForceRange		= {2500, 3650};
			lifespanRange		= {7, 17};
			spawnTimeRange		= {3, 4};
			break;
		
		case HARD:
			maxCount			= 5;
			widthRange			= {20, 130};
			heightRange			= {20, 130};
			maxVelocityRange	= {750, 1350};
			maxForceRange		= {2650, 3650};
			lifespanRange		= {4, 17};
			spawnTimeRange		= {2, 4};
			break;
		
		case INSANE:
			maxCount			= 6;
			widthRange			= {10, 55};
			heightRange			= {10, 55};
			maxVelocityRange	= {750, 1350};
			maxForceRange		= {2650, 3650};
			lifespanRange		= {4, 17};
			spawnTimeRange		= {2, 3};
			break;
	}
}