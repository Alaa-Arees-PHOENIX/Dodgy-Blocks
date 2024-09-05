#ifndef ENEMYBLOCK_DB
#define ENEMYBLOCK_DB

#include "Enemy.hpp"
#include "MotiveCreature.hpp"

class Player;

class EnemyBlock : public MotiveCreature, public Enemy
{
public:
	static constexpr float DENSITY_OF_BLOCKS = 8.81745e-4; // used to calculate the mass, where mass = width*height*density
private:
	static int objectsCount; // used to get the current number of instances of EnemyBlock class.
	int width, height;
	
	// warning rectangles will draw a small rectangle on the edges when the enemy is outside the screen:
	Rectangle warningUp, warningDown, warningLeft, warningRight;
	
public:
	EnemyBlock (Vector2 MAX_VELOCITY, Vector2 ACC_FORCE, float MASS, Vector2 initialPos,
				int lifespan,
				int width, int height);
	~EnemyBlock ();
	Player& pick_target ();
	void update (float dt) override;
	void draw () override;
	
	static int get_instances_count() {return objectsCount;}
};

#endif // ENEMYBLOCK_DB