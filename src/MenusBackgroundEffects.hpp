#ifndef MENUSBACKGROUNDEFFECTS_DB
#define MENUSBACKGROUNDEFFECTS_DB

#include <vector>
#include "raylib.h"
#include "Logger.hpp"

class MenusBackgroundEffects
{
public:
	void initilize ();
	void launchBall ();
	void animate_recs ();
	void update (float dt);
	void draw ();
	
private:
	/* FloatingRectangle is a MotiveCreature but this one has a special movement mechanisim
		so I decided to NOT make it inherit from MotiveCreature */
	class FloatingRectangle
	{
	public:
		void set_target ();
		void initilize ();
		void update (float dt);
		void draw ();
		
	private:
		Rectangle body;
		Vector2 target;
	};
    
	class FlyingBall : public Logger::Listener
	{
	public:
		FlyingBall ();
		virtual ~FlyingBall ();
		void bounce_on_edges (float dt);
		void update (float dt);
		void draw ();
		void logInfo (int logTime, bool useDefaultLogFile, const char* alternativeFile);
		
		void bounce_up (float dt)
		{
            velocity.y = -abs (velocity.y);
            if (abs (velocity.y) <= acceleration.y * dt) {velocity.y = 0;}
            else {velocity.y += acceleration.y * dt;} // v is negative, it will loose energy here
        }
        void bounce_left () {velocity.x = -abs (velocity.x);}
        void bounce_right () {velocity.x = +abs (velocity.x);}
		
		/*	used to calculate the mass, where mass = PI*(radius^2)*density:	*/
		static constexpr float DENSITY_OF_BALLS = 8.81745e-4;
		
	private:
		int radius;
        Vector2 position, velocity, acceleration;
	};
    
    FloatingRectangle floatingRecs[10];
    short numOfFloatingRecs = 0;
    std::vector <FlyingBall> flyingBalls;
};

#endif // MENUSBACKGROUNDEFFECTS_DB