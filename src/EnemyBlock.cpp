#include <iostream> // TEMP
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
	// same height with a small width, pos on the y-axis for left/right warnings doesn't matter it's variable
	warningLeft		= {-SCREEN_WIDTH/2.0f, 0, 11, (float)height}; 
	warningRight	= {SCREEN_WIDTH/2.0f - 11, 0, 11, (float)height};
	warningUp		= {0, -SCREEN_HEIGHT/2.0f, (float)width, 11};
	warningDown		= {0, SCREEN_HEIGHT/2.0f - 11, (float)width, 11};
	
	objectsCount++;
}

EnemyBlock::~EnemyBlock ()
{
	objectsCount--;
}

Player& EnemyBlock::pick_target ()
{
	if (!GAME_WORLD.P2().is_active()) {return GAME_WORLD.P1();} // playing singleplayer
	
	float disFromP1, disFromP2;
	disFromP1 = (get_posX() - GAME_WORLD.P1().get_posX()) * (get_posX() - GAME_WORLD.P1().get_posX()) +
				(get_posY() - GAME_WORLD.P1().get_posY()) * (get_posY() - GAME_WORLD.P1().get_posY());
	disFromP2 = (get_posX() - GAME_WORLD.P2().get_posX()) * (get_posX() - GAME_WORLD.P2().get_posX()) +
				(get_posY() - GAME_WORLD.P2().get_posY()) * (get_posY() - GAME_WORLD.P2().get_posY());
	
	if ((disFromP1 < disFromP2 && !GAME_WORLD.P1().is_dead()) || GAME_WORLD.P2().is_dead()){
		return GAME_WORLD.P1();
	}
	else {return GAME_WORLD.P2();}
}

void EnemyBlock::update (float dt)
{
	Player& target = pick_target ();
	Rectangle body = {position.x, position.y, (float)width, (float)height};
	
	if (position.y > target.get_posY()) 		{accelerate_up (dt);}
	else if (position.y < target.get_posY()) 	{accelerate_down (dt);}

	if (position.x > target.get_posX()) 		{accelerate_left (dt);}
	else if (position.x < target.get_posX()) 	{accelerate_right (dt);}

	// actual movement
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;

	// check if the enemy hits a player
	if (CheckCollisionCircleRec (GAME_WORLD.P1().get_pos(), GAME_WORLD.P1().get_radius(), body) &&
		!GAME_WORLD.P1().is_dead())
	{
		GAME_WORLD.P1().kill();
	}

	else if (	GAME_WORLD.P2().is_active() &&
				CheckCollisionCircleRec (GAME_WORLD.P2().get_pos (), GAME_WORLD.P2().get_radius(), body) &&
				!GAME_WORLD.P2().is_dead())
	{
		GAME_WORLD.P2().kill();
	}
	
	// update warning signs:
	warningLeft.y	= position.y;
	warningRight.y	= position.y;
	warningUp.x		= position.x;
	warningDown.x	= position.x;
}

void EnemyBlock::draw ()
{
	DrawRectangle (position.x, position.y, width, height, BLACK);
	
	// check and draw a warning sign if the enemy is outside the screen:
	Vector2 pos = GetWorldToScreen2D (position, CAMERA);
	if (pos.x + width < 0)						{DrawRectangleRec (warningLeft, ColorAlpha (BLACK, 0.58f));}
	if (pos.x > CURRENT_SCREEN_WIDTH)			{DrawRectangleRec (warningRight, ColorAlpha (BLACK, 0.58f));}
	if (pos.y < 0)								{DrawRectangleRec (warningUp, ColorAlpha (BLACK, 0.58f));}
	if (pos.y + height > CURRENT_SCREEN_HEIGHT)	{DrawRectangleRec (warningDown, ColorAlpha (BLACK, 0.58f));}
}