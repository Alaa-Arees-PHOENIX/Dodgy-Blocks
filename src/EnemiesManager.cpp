#include "raylib.h"
#include "EnemyBlock.hpp"
#include "EnemiesManager.hpp"
#include "global_resources.hpp"

EnemiesManager::EnemiesManager ()
{
	reset();
}

void EnemiesManager::reset ()
{
	for (auto it = enemies.begin(); it != enemies.end(); it++) {delete *it;}
	enemies.clear();
	nextSpawnTimeForBlocks = 3;
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
	if (TIMER.get_time () < nextSpawnTimeForBlocks || EnemyBlock::get_instances_count() >= MAX_BLOCKS_COUNT) {return;}
	
	float width = (float)random_number (37, 111);
	float height = (float)random_number (37, 111);
	
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
		initialPos = {CURRENT_SCREEN_WIDTH/2.0f - 190, (float)random_number (-CURRENT_SCREEN_HEIGHT/2, CURRENT_SCREEN_HEIGHT/2)};
		break;
		case 4: // right
		initialPos = {CURRENT_SCREEN_WIDTH/2.0f + 190, (float)random_number (-CURRENT_SCREEN_HEIGHT/2, CURRENT_SCREEN_HEIGHT/2.0f)};
		break;
	}
	
	Vector2 maxVelocity = {(float)random_number (800, 1300), (float)random_number (800, 1300)};
	Vector2 accForce = {(float)random_number (2500, 3650), (float)random_number (2500, 3650)};
	float mass = width*height*EnemyBlock::DENSITY_OF_BLOCKS;
	
	int lifespan = random_number (7, 17);
	
	enemies.insert (new EnemyBlock (maxVelocity, accForce, mass, initialPos, lifespan, width, height));
	nextSpawnTimeForBlocks += random_number (2, 5);
}