#ifndef MENUSBACKGROUNDEFFECTS_DB
#define MENUSBACKGROUNDEFFECTS_DB

#include <vector>
#include "raylib.h"
#include "MotiveCreature.hpp"

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
    
	class FlyingBall : public MotiveCreature
	{
	public:
		FlyingBall (Vector2 MAX_VELOCITY, Vector2 ACC_FORCE, float MASS, int radius);
		virtual ~FlyingBall ();
		void bounce_on_edges (float dt);
		void update (float dt) override;
		void draw () override;
		void logInfo (int logTime, bool useDefaultLogFile, const char* alternativeFile) override;
		
		/*	used to calculate the mass, where mass = PI*(radius^2)*density:	*/
		static constexpr float DENSITY_OF_BALLS = 8.81745e-4;
		
	private:
		int radius;
	};
    
    FloatingRectangle floatingRecs[10];
    short numOfFloatingRecs = 0;
    std::vector <FlyingBall> flyingBalls;
};

#endif // MENUSBACKGROUNDEFFECTS_DB