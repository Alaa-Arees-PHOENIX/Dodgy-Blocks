#include <tuple>
#include <cmath>
#include "raylib.h"
#include "MotiveCreature.hpp"
#include "Player.hpp"
#include "global_resources.hpp"

Player::Player (Vector2 MAX_VELOCITY, Vector2 ACC_FORCE, float MASS, Color color)
	: MotiveCreature (MAX_VELOCITY, ACC_FORCE, MASS), color (color)
{
	radius = 19;
}

void Player::set_controls (std::tuple <KeyboardKey, KeyboardKey, KeyboardKey, KeyboardKey> controls)
{
    std::tie (UP, DOWN, LEFT, RIGHT) = controls;
}
    
void Player::update (float dt)
{	
	// acceleration:
	if (IsKeyDown (UP))              			{accelerate_up (dt);}
    else if (IsKeyDown (DOWN))  				{accelerate_down (dt);}
    else if (IsKeyUp (UP) && velocity.y < 0)    {accelerate_down (dt);}
    else if (IsKeyUp (DOWN) && velocity.y > 0)  {accelerate_up (dt);}
    
    if (IsKeyDown (LEFT))          				{accelerate_left (dt);}
    else if (IsKeyDown (RIGHT))   				{accelerate_right (dt);}
    else if (IsKeyUp (LEFT) && velocity.x < 0)  {accelerate_right (dt);}
    else if (IsKeyUp (RIGHT) && velocity.x > 0) {accelerate_left (dt);}
    
	// fix precision and never-ending movement errors:
	if (abs (velocity.x) * dt < 0.3f) {velocity.x = 0;}
    if (abs (velocity.y) * dt < 0.3f) {velocity.y = 0;}
	
	// just read the function's name...
    bounce_on_edges (dt);
    
	// actuale movement:
    position.x += velocity.x*dt;
	position.y += velocity.y*dt;
}
    
void Player::draw ()
{
    DrawCircle (position.x, position.y, radius, color);
}

void Player::initilize ()
{
	position = {(float)random_number (-CURRENT_SCREEN_WIDTH/2 + radius, CURRENT_SCREEN_WIDTH/2 - radius),
				(float)random_number (-CURRENT_SCREEN_HEIGHT/2 + radius, CURRENT_SCREEN_HEIGHT/2 - radius)};
	velocity = {0, 0};
	dead = 0;
	survivedFor = 0;
}

void Player::kill ()
{
	dead = 1;
	survivedFor = TIMER.get_time ();
}

void Player::bounce_on_edges (float dt)
{
	Vector2 pos = GetWorldToScreen2D (position, CAMERA);
	
	// player will gain energy (velocity) when bouncing, so '-1' is passed to the 'bounce' method.
    if (pos.y - radius <= 0)							{bounce_down (-1, dt);}
    else if (pos.y + radius >= CURRENT_SCREEN_HEIGHT)	{bounce_up (-1, dt);}
    if (pos.x - radius <= 0)							{bounce_right (-1, dt);}
    else if (pos.x + radius >= CURRENT_SCREEN_WIDTH)	{bounce_left (-1, dt);}
}