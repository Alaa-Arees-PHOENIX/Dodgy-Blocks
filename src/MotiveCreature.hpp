#ifndef MOTIVECREATURE_DB
#define MOTIVECREATURE_DB

#include <cmath>
#include "raylib.h"
#include "raymath.h"

class MotiveCreature
{
protected:
	Vector2 position, velocity;
	const Vector2 MAX_VELOCITY;
	const Vector2 ACC_FORCE; // ACC_FORCE <=> acceleration_force
	const float MASS; // ACC_FORCE/MASS = acceleration
	
protected:
	MotiveCreature (Vector2 MAX_VELOCITY, Vector2 ACC_FORCE, float MASS, Vector2 initialPos = {0, 0});
	virtual ~MotiveCreature ();
	
public:
	virtual void update (float dt) = 0;
	virtual void draw () = 0;
	
	// getters and setters:
	void set_pos (Vector2 pos) {position = pos;}
	float get_posX () 	{return position.x;}
	float get_posY () 	{return position.y;}
	Vector2 get_pos () 	{return position;}
	
protected:
	void accelerate_up	 (float dt)	{velocity.y = std::max (velocity.y - (ACC_FORCE.y/MASS)*dt, -MAX_VELOCITY.y);}
	void accelerate_down (float dt) {velocity.y = std::min (velocity.y + (ACC_FORCE.y/MASS)*dt, MAX_VELOCITY.y);}
	void accelerate_left (float dt) {velocity.x = std::max (velocity.x - (ACC_FORCE.x/MASS)*dt, -MAX_VELOCITY.x);}
	void accelerate_right(float dt)	{velocity.x = std::min (velocity.x + (ACC_FORCE.x/MASS)*dt, MAX_VELOCITY.x);}
	
	// if decay type is 1 it will decrease velocity on each bounce
	// if decay type is -1 it will increase velocity on each bounce
	// if decay type is 0 it will only reverse the direction of velocity with no effect on the magnitude
	void bounce_up (short decay, float dt)		{velocity.y = -abs (velocity.y) + (decay * (ACC_FORCE.y / MASS) * dt);}
	void bounce_down (short decay, float dt)	{velocity.y = abs  (velocity.y) - (decay * (ACC_FORCE.y / MASS) * dt);}
	void bounce_left (short decay, float dt)	{velocity.x = -abs (velocity.x) + (decay * (ACC_FORCE.y / MASS) * dt);}
	void bounce_right (short decay, float dt)	{velocity.x = abs  (velocity.x) - (decay * (ACC_FORCE.y / MASS) * dt);}
	
};

#endif