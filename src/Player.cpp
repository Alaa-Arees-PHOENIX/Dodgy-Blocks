#include <tuple>
#include <cmath>
#include "raylib.h"
#include "MotiveCreature.hpp"
#include "Player.hpp"
#include "global_resources.hpp"

Player::Player (Vector2 MAX_VELOCITY, Vector2 ACC_FORCE, float MASS, Color color)
	: MotiveCreature (MAX_VELOCITY, ACC_FORCE, MASS), color (color)
{
	
}

Player::Player ()
	:	Player ({0, 0}, {0, 0}, 0, BLACK)
{
	
}

void Player::set_keyboard_control (std::tuple <KeyboardKey, KeyboardKey, KeyboardKey, KeyboardKey> controls)
{
    std::tie (UP, DOWN, LEFT, RIGHT) = controls;
	useMouse = 0;
}

void Player::set_mouse_control ()
{
	std::tie (UP, DOWN, LEFT, RIGHT) = (std::tuple<KeyboardKey, KeyboardKey, KeyboardKey, KeyboardKey>){KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL};
	useMouse = 1;
}
    
void Player::update (float dt)
{	
	// acceleration:
	if		(should_accelerate_up ())		{accelerate_up (dt);}
    else if	(should_accelerate_down ())		{accelerate_down (dt);}
    
    if		(should_accelerate_left ())		{accelerate_left (dt);}
    else if	(should_accelerate_right ())	{accelerate_right (dt);}
    
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
    DrawCircle (position.x, position.y, RADIUS, color);
}

void Player::initilize ()
{
	position = {(float)random_number (-SCREEN_WIDTH/2 + RADIUS, SCREEN_WIDTH/2 - RADIUS),
				(float)random_number (-SCREEN_HEIGHT/2 + RADIUS, SCREEN_HEIGHT/2 - RADIUS)};
	velocity = {0, 0};
	dead = 0;
	survivedFor = 0;
}

void Player::kill ()
{
	dead = 1;
	survivedFor = TIMER.get_time ();
}

bool Player::should_accelerate_up ()
{
	return ((!useMouse && IsKeyDown (UP)) ||
			(!useMouse && IsKeyUp (DOWN) && velocity.y > 0) ||
			(useMouse && (GetScreenToWorld2D (GetMousePosition(), CAMERA).y < position.y)));
}

bool Player::should_accelerate_down ()
{
	return ((!useMouse && IsKeyDown (DOWN)) ||
			(!useMouse && IsKeyUp (UP) && velocity.y < 0) ||
			(useMouse && (GetScreenToWorld2D (GetMousePosition(), CAMERA).y > position.y)));
}

bool Player::should_accelerate_left ()
{
	return ((!useMouse && IsKeyDown (LEFT)) ||
			(!useMouse && IsKeyUp (RIGHT) && velocity.x > 0) ||
			(useMouse && (GetScreenToWorld2D (GetMousePosition(), CAMERA).x < position.x)));
}

bool Player::should_accelerate_right ()
{
	return ((!useMouse && IsKeyDown (RIGHT)) ||
			(!useMouse && IsKeyUp (LEFT) && velocity.x < 0) ||
			(useMouse && (GetScreenToWorld2D (GetMousePosition(), CAMERA).x > position.x)));
}

void Player::bounce_on_edges (float dt)
{
	Vector2 pos = GetWorldToScreen2D (position, CAMERA);
	
	// player will gain energy (velocity) when bouncing, so '-1' is passed to the 'bounce' method.
    if (pos.y - RADIUS <= 0)							{bounce_down (-1, dt);}
    else if (pos.y + RADIUS >= CURRENT_SCREEN_HEIGHT)	{bounce_up (-1, dt);}
    if (pos.x - RADIUS <= 0)							{bounce_right (-1, dt);}
    else if (pos.x + RADIUS >= CURRENT_SCREEN_WIDTH)	{bounce_left (-1, dt);}
}