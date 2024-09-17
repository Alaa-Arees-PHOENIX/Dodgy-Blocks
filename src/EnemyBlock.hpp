#ifndef ENEMYBLOCK_DB
#define ENEMYBLOCK_DB

#include "Enemy.hpp"
#include "MotiveCreature.hpp"
#include "Logger.hpp"

class EnemyBlock : public MotiveCreature, public Enemy
{
public:
	EnemyBlock (Vector2 MAX_VELOCITY, Vector2 ACC_FORCE, float MASS, Vector2 initialPos,
				int lifespan,
				int width, int height);
	virtual ~EnemyBlock ();
	void update (float dt) override;
	void draw () override;
	void logInfo (	int logTime,
					bool useDefaultLogFile = 1,
					const char* alternativeFile = "\0") override;
	
	static int get_instances_count() {return objectsCount;}
	int get_width ()	{return width;}
	int get_height ()	{return height;}
	
public:
/*	used to calculate the mass, where mass = width*height*density:	*/
	static constexpr float DENSITY_OF_BLOCKS = 8.81745e-4;
	
private:
/*	used to get the current number of instances of EnemyBlock class:	*/
	static int objectsCount;
	int width, height;
	
/*	warning rectangles will draw a small rectangle on the edges when the enemy is outside the screen:	*/
	Rectangle warningUp, warningDown, warningLeft, warningRight;
};

#endif // ENEMYBLOCK_DB