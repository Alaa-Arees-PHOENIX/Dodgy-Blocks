#include <fstream>
#include "raylib.h"
#include "MenusBackgroundEffects.hpp"
#include "global_resources.hpp"

void MenusBackgroundEffects::initilize ()
{
	numOfFloatingRecs = random_number (3, 8);
	for (int i=0; i < numOfFloatingRecs; i++) {floatingRecs[i].initilize ();}

	flyingBalls.clear ();
}

void MenusBackgroundEffects::launchBall ()
{
	int radius = random_number (5, 30);
	flyingBalls.push_back (FlyingBall ({9999, 2100}, {1000, 3600}, PI*radius*radius*FlyingBall::DENSITY_OF_BALLS, radius));
}

void MenusBackgroundEffects::animate_recs ()
{
	for (int i=0; i < numOfFloatingRecs; i++) {floatingRecs[i].set_target ();}
}

void MenusBackgroundEffects::update (float dt)
{
	for (int i=0; i < numOfFloatingRecs; i++) {floatingRecs[i].update (dt);}
	if (flyingBalls.empty ()) {return;}
	for (auto it = flyingBalls.begin (); it != flyingBalls.end (); it++) {it -> update (dt);}
}

void MenusBackgroundEffects::draw ()
{
	for (int i=0; i < numOfFloatingRecs; i++) {floatingRecs[i].draw ();}
	if (flyingBalls.empty ()) {return;}
	for (auto it = flyingBalls.begin(); it != flyingBalls.end(); it++) {it -> draw ();}
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
	body.x = lerp (body.x, target.x, exponential); // it was: (target.x, body.x, exponential);
	body.y = lerp (body.y, target.y, exponential); // it was: (target.y, body.y, exponential);
}

void MenusBackgroundEffects::FloatingRectangle::draw ()
{
	DrawRectangleRec (body, BLACK);
}



MenusBackgroundEffects::FlyingBall::FlyingBall (	Vector2 MAX_VELOCITY,
														Vector2 ACC_FORCE,
														float MASS,
														int radius)
		: MotiveCreature (MAX_VELOCITY, ACC_FORCE, MASS), radius (radius)
{
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
	
	#if defined(DEBUG)
		LOGGER.add_listener (this);
	#endif
}

MenusBackgroundEffects::FlyingBall::~FlyingBall ()
{
	#if defined(DEBUG)
		LOGGER.remove_listener (this);
	#endif
}

void MenusBackgroundEffects::FlyingBall::bounce_on_edges (float dt)
{
	if (position.y + radius >= CURRENT_SCREEN_HEIGHT/2)	{bounce_down (1, dt);}
	if (position.x - radius <= -CURRENT_SCREEN_WIDTH/2)	{bounce_left (0, dt);}
	if (position.x + radius >= CURRENT_SCREEN_WIDTH/2)	{bounce_right (0, dt);}
		
	if (abs (velocity.y) <= (ACC_FORCE.y/MASS) * dt) {velocity.y = 0;}
}

void MenusBackgroundEffects::FlyingBall::update (float dt)
{
	accelerate_down (dt);
	
	/* friction */
	velocity.x *= 0.99;
	velocity.y *= 0.99;
	
	bounce_on_edges (dt);
	
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
}

void MenusBackgroundEffects::FlyingBall::draw ()
{
	DrawCircle (position.x, position.y, radius, BLACK);
}

void MenusBackgroundEffects::FlyingBall::logInfo (int logTime, bool useDefaultLogFile, const char* alternativeFile)
{
	std::ofstream logFile;
	std::string logFilePath = useDefaultLogFile ? "log/FlyingBall_log.txt" : alternativeFile;
	logFile.open(logFilePath.c_str(), std::ios_base::app);

	logFile << Logger::LINE_BREAK;

	logFile << "FlyingBall instance, logged at: " << logTime << '\n';
	logFile << "game time: " << TIMER.get_time() << '\n';
	logFile << "address: " << this << '\n';
	logFile << "radius = " << radius << '\n';
	logFile << "#### Inherits from MotiveCreature ####\n";
	logFile.close();
	MotiveCreature::logInfo (logTime, 0, "log/FlyingBall_log.txt");
	logFile.open(logFilePath.c_str(), std::ios_base::app);
	logFile << "#### End of inheritance ####\n";

	logFile << Logger::LINE_BREAK;
}
