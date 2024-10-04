#include <fstream>
#include "raylib.h"
#include "MenusBackgroundEffects.hpp"
#include "global_resources.hpp"

void MenusBackgroundEffects::initilize ()
{
	numOfFloatingRecs = random_number (3, 8);
	for (int i=0; i < numOfFloatingRecs; i++) {floatingRecs[i].initilize ();}

	cannonBalls.clear ();
}

void MenusBackgroundEffects::launch_cannon ()
{
	cannonBalls.push_back (CannonBall ());
	float pitch = 15.0f/(cannonBalls.back().get_radius());
	pitch = std::max (pitch, 0.8f); // minimum pitch
	pitch = std::min (pitch, 1.7f); // maximum pitch
	AUDIO_MANAGER.play_cannon_ball_sound (pitch);
}

void MenusBackgroundEffects::animate_recs ()
{
	for (int i=0; i < numOfFloatingRecs; i++) {floatingRecs[i].set_target ();}
}

void MenusBackgroundEffects::update (float dt)
{
	for (int i=0; i < numOfFloatingRecs; i++) {floatingRecs[i].update (dt);}
	if (cannonBalls.empty ()) {return;}
	for (auto it = cannonBalls.begin (); it != cannonBalls.end (); it++) {it -> update (dt);}
}

void MenusBackgroundEffects::draw ()
{
	for (int i=0; i < numOfFloatingRecs; i++) {floatingRecs[i].draw ();}
	if (cannonBalls.empty ()) {return;}
	for (auto it = cannonBalls.begin(); it != cannonBalls.end(); it++) {it -> draw ();}
}

/*********** NESTED INACCESSIBLE METHODS *************/

void MenusBackgroundEffects::FloatingRectangle::set_target ()
{
	float x = (float)random_number (-CURRENT_SCREEN_WIDTH/2, CURRENT_SCREEN_WIDTH/2);
	float y = (float)random_number (-CURRENT_SCREEN_HEIGHT/2, CURRENT_SCREEN_HEIGHT/2);
	target = {x, y};
}

void MenusBackgroundEffects::FloatingRectangle::initilize ()
{
	body = {0, 0, (float)random_number (37, 149), (float)random_number (37, 149)};
	set_target ();
}

void MenusBackgroundEffects::FloatingRectangle::update (float dt)
{
	float lerpSpeed = random_number (1, 9) / 10.0f;
	float exponential = pow (lerpSpeed, dt * lerpSpeed);
	body.x = lerp (body.x, target.x, exponential);
	body.y = lerp (body.y, target.y, exponential);
}

void MenusBackgroundEffects::FloatingRectangle::draw ()
{
	DrawRectangleRec (body, dark_mode_processor (BLACK));
}



MenusBackgroundEffects::CannonBall::CannonBall ()
{
	radius = random_number (5, 30);
	float x = 0, y = 0;
	int whichSideToSpawnFrom = random_number (1, 2);
	switch (whichSideToSpawnFrom)
	{
		case 1: // left
			x = -(CURRENT_SCREEN_WIDTH/2) - radius;
			y = random_number (-CURRENT_SCREEN_HEIGHT/2, CURRENT_SCREEN_HEIGHT/2 - 2*radius);
			break;
		case 2: // right
			x = (CURRENT_SCREEN_WIDTH/2) + radius;
			y = random_number (-CURRENT_SCREEN_HEIGHT/2, CURRENT_SCREEN_HEIGHT/2 - 2*radius);
			break;
	}
	position = {x, y}; // initial position
	velocity.x = random_number (600, 2000); // initial velocity
	velocity.y = random_number (-1800, 0);
	acceleration.x = 100;
	acceleration.y = 3600; // gravity
	
	#if defined(DEBUG)
		LOGGER.add_listener (this);
	#endif
}

MenusBackgroundEffects::CannonBall::~CannonBall ()
{
	#if defined(DEBUG)
		LOGGER.remove_listener (this);
	#endif
}

void MenusBackgroundEffects::CannonBall::bounce_on_edges (float dt)
{
	Vector2 pos = GetWorldToScreen2D (position, CAMERA);
	if (pos.y + radius >= CURRENT_SCREEN_HEIGHT)	{bounce_up (dt);}
	if (pos.x - radius <= 0)            			{bounce_right ();}
	if (pos.x + radius >= CURRENT_SCREEN_WIDTH)		{bounce_left ();}
}

void MenusBackgroundEffects::CannonBall::update (float dt)
{
	// accelerate_down (dt);
	
	bool limitDown = ((velocity.y < 2100) && (GetWorldToScreen2D (position, CAMERA).y + radius < CURRENT_SCREEN_HEIGHT));
	if (velocity.y < 0)                 {velocity.y += acceleration.y * dt;}
	if (velocity.y > 0 && limitDown)    {velocity.y += acceleration.y * dt;}
	
	/* friction */
	velocity.x *= 0.99;
	velocity.y *= 0.99;
	
	bounce_on_edges (dt);
	
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
}

void MenusBackgroundEffects::CannonBall::draw ()
{
	DrawCircle (position.x, position.y, radius, dark_mode_processor (BLACK));
}

void MenusBackgroundEffects::CannonBall::log_info (int logTime, bool useDefaultLogFile, const char* alternativeFile)
{
	std::ofstream logFile;
	std::string logFilePath = useDefaultLogFile ? "log/CannonBall_log.txt" : alternativeFile;
	logFile.open(logFilePath.c_str(), std::ios_base::app);

	logFile << Logger::LINE_BREAK;

	logFile << "CannonBall instance, logged at: " << logTime << '\n';
	logFile << "game time: " << TIMER.get_time() << '\n';
	logFile << "address: " << this << '\n';
	logFile << "radius = " << radius << '\n';
	logFile << "position = " << to_string (position) << '\n';
	logFile << "velocity = " << to_string (velocity) << '\n';
	logFile << "acceleration = " << to_string (acceleration) << '\n';

	logFile << Logger::LINE_BREAK;
}
