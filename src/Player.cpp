#include <tuple>
#include <cmath>
#include <fstream>
#include "raylib.h"
#include "MotiveCreature.hpp"
#include "Player.hpp"
#include "global_resources.hpp"

Player::Player (Vector2 MAX_VELOCITY, Vector2 ACC_FORCE, float MASS, Color color)
	: MotiveCreature (MAX_VELOCITY, ACC_FORCE, MASS), color (color)
{
	#if defined(DEBUG)
		LOGGER.add_listener (this);
	#endif
}

Player::Player ()
	:	Player ({0, 0}, {0, 0}, 0, BLACK)
{
	
}

Player::~Player ()
{
	#if defined(DEBUG)
		LOGGER.remove_listener (this);
	#endif
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
	if (!useMouse){
		return (IsKeyDown (UP) || (IsKeyUp (DOWN) && velocity.y > 0));
	}
	else{
		return ((IsMouseButtonDown (MOUSE_BUTTON_LEFT) && (GetScreenToWorld2D (GetMousePosition(), CAMERA).y < position.y))
				||
				(IsMouseButtonUp (MOUSE_BUTTON_LEFT) && velocity.y > 0));
	}
}

bool Player::should_accelerate_down ()
{
	if (!useMouse){
		return (IsKeyDown (DOWN) || (IsKeyUp (UP) && velocity.y < 0));
	}
	else{
		return ((IsMouseButtonDown (MOUSE_BUTTON_LEFT) && (GetScreenToWorld2D (GetMousePosition(), CAMERA).y > position.y))
				||
				(IsMouseButtonUp (MOUSE_BUTTON_LEFT) && velocity.y < 0));
	}
}

bool Player::should_accelerate_left ()
{
	if (!useMouse){
		return (IsKeyDown (LEFT) || (IsKeyUp (RIGHT) && velocity.x > 0));
	}
	else{
		return ((IsMouseButtonDown (MOUSE_BUTTON_LEFT) && (GetScreenToWorld2D (GetMousePosition(), CAMERA).x < position.x))
				||
				(IsMouseButtonUp (MOUSE_BUTTON_LEFT) && velocity.x > 0));
	}
}

bool Player::should_accelerate_right ()
{
	if (!useMouse){
		return (IsKeyDown (RIGHT) || (IsKeyUp (LEFT) && velocity.x < 0));
	}
	else{
		return ((IsMouseButtonDown (MOUSE_BUTTON_LEFT) && (GetScreenToWorld2D (GetMousePosition(), CAMERA).x > position.x))
				||
				(IsMouseButtonUp (MOUSE_BUTTON_LEFT) && velocity.x < 0));
	}
}

void Player::draw_statistics (short playerID)
{
	int fontSize = 37;
	
	std::string playerColor;
	switch (playerID)
	{
		case 0: playerColor = "Red"; break;
		case 1: playerColor = "Blue"; break;
		case 2: playerColor = "Green"; break;
	}
	
	std::string stats = playerColor + " player has survived for " + std::to_string (survivedFor) + " seconds.";
	int x = -MeasureText (stats.c_str(), fontSize)/2; // centered in the middle of screen
	int y = -SCREEN_HEIGHT/4 + 75*(playerID); // initial y-position + vertical spacing
	
	DrawText (stats.c_str(), x, y, fontSize, color);
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

void Player::logInfo (int logTime, bool useDefaultLogFile, const char* alternativeFile)
{
	std::ofstream logFile;
	std::string logFilePath = useDefaultLogFile ? "log/Player_log.txt" : alternativeFile;
	logFile.open(logFilePath.c_str(), std::ios_base::app);

	logFile << Logger::LINE_BREAK;

	logFile << "Player instance, logged at: " << logTime << '\n';
	logFile << "game time: " << TIMER.get_time() << '\n';
	logFile << "address: " << this << '\n';
	logFile << "is active? " << active << '\n';
	logFile << "is dead? " << dead << '\n';
	logFile << "survival time " << survivedFor << '\n';
	logFile << "use mouse? " << useMouse << '\n';
	logFile << "#### Inherits from MotiveCreature ####\n";
	logFile.close();
	MotiveCreature::logInfo (logTime, 0, "log/Player_log.txt");
	logFile.open(logFilePath.c_str(), std::ios_base::app);
	logFile << "#### End of inheritance ####\n";

	logFile << Logger::LINE_BREAK;
}
