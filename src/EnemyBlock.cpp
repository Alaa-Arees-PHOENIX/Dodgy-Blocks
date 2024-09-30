#include <iostream>
#include <fstream>
#include "raylib.h"
#include "EnemyBlock.hpp"
#include "Player.hpp"
#include "global_resources.hpp"

int EnemyBlock::objectsCount = 0;

EnemyBlock::EnemyBlock (Vector2 MAX_VELOCITY, Vector2 ACC_FORCE, float MASS, Vector2 initialPos,
						int lifespan,
						int width, int height)
	: 	MotiveCreature (MAX_VELOCITY, ACC_FORCE, MASS, initialPos),
		Enemy (lifespan),
		width (width), height (height)
{
/*	same height with a small width, pos on the y-axis for left/right warnings doesn't matter it's variable	*/
	warningLeft		= {-SCREEN_WIDTH/2.0f, 0, 11, (float)height}; 
	warningRight	= {SCREEN_WIDTH/2.0f - 11, 0, 11, (float)height};
	warningUp		= {0, -SCREEN_HEIGHT/2.0f, (float)width, 11};
	warningDown		= {0, SCREEN_HEIGHT/2.0f - 11, (float)width, 11};
	
	objectsCount++;
	
	#if defined(DEBUG)
		std::cerr << "EnemyBlock created " << SPAWN_TIME << ' ' << DEATH_TIME << std::endl;
		LOGGER.add_listener (this);
	#endif
}

EnemyBlock::~EnemyBlock ()
{
	objectsCount--;
	#if defined(DEBUG)
		std::cerr << "EnemyBlock destroy\n";
		LOGGER.remove_listener (this);
	#endif
}

void EnemyBlock::update (float dt)
{
	Player& target = PLAYERS_MANAGER.pick_target_for_enemy (position);
	
	if (position.y > target.get_posY()) 		{accelerate_up (dt);}
	else if (position.y < target.get_posY()) 	{accelerate_down (dt);}

	if (position.x > target.get_posX()) 		{accelerate_left (dt);}
	else if (position.x < target.get_posX()) 	{accelerate_right (dt);}

/*	actual movement:	*/
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
	
	PLAYERS_MANAGER.collide_EnemyBlock_with_players (*this);
	
/*	update warning signs:	*/
	Vector2 pos = GetWorldToScreen2D (position, CAMERA);
	
	warningLeft.y	= std::max (pos.y, -height/2.0f);
	warningLeft.y	= std::min (pos.y, CURRENT_SCREEN_HEIGHT - height/2.0f);
	warningLeft.y	= GetScreenToWorld2D ({warningLeft.x, warningLeft.y}, CAMERA).y;
	warningRight.y	= warningLeft.y;
	
	warningUp.x		= std::max (pos.x, -width/2.0f);
	warningUp.x		= std::min (pos.x, CURRENT_SCREEN_WIDTH - width/2.0f);
	warningUp.x		= GetScreenToWorld2D ({warningUp.x, warningUp.y}, CAMERA).x;
	warningDown.x	= warningUp.x;
}

void EnemyBlock::draw ()
{
	DrawRectangle (position.x, position.y, width, height, BLACK);
	
/*	check and draw a warning sign if the enemy is outside the screen:	*/
	Vector2 pos = GetWorldToScreen2D (position, CAMERA);
	
	if (pos.x < 0)
		{DrawRectangleRec (warningLeft, ColorAlpha (BLACK, 0.58f));}
	
	if (pos.x + width > CURRENT_SCREEN_WIDTH)
		{DrawRectangleRec (warningRight, ColorAlpha (BLACK, 0.58f));}
	
	if (pos.y < 0)
		{DrawRectangleRec (warningUp, ColorAlpha (BLACK, 0.58f));}
	
	if (pos.y + height > CURRENT_SCREEN_HEIGHT)
		{DrawRectangleRec (warningDown, ColorAlpha (BLACK, 0.58f));}
}

void EnemyBlock::log_info (int logTime, bool useDefaultLogFile, const char* alternativeFile)
{
	std::ofstream logFile;
	std::string logFilePath = useDefaultLogFile ? "log/EnemyBlock_log.txt" : alternativeFile;
	logFile.open(logFilePath.c_str(), std::ios_base::app);
	
	logFile << Logger::LINE_BREAK;
	
	logFile << "EnemyBlock instance, logged at " << logTime << '\n';
	logFile << "game time: " << TIMER.get_time() << '\n';
	logFile << "address: " << this << '\n';
	logFile << "objects count = " << objectsCount << '\n';
	logFile << "width = " << width << ", height = " << height << '\n';
	logFile << "warningUp = " << to_string (warningUp) << '\n';
	logFile << "warningDown = " << to_string (warningDown) << '\n';
	logFile << "warningLeft = " << to_string (warningLeft) << '\n';
	logFile << "warningRight = " << to_string (warningRight) << '\n';
	
	logFile << "##### Inherits from MotiveCreature and Enemy ####\n";
	logFile.close();
	MotiveCreature::log_info (logTime, 0, "log/EnemyBlock_log.txt");
	Enemy::log_info (logTime, 0, "log/EnemyBlock_log.txt");	
	logFile.open(logFilePath.c_str(), std::ios_base::app);
	logFile << "##### End of inheritance ####\n";
	
	logFile << Logger::LINE_BREAK;
	
	logFile.close();
}
