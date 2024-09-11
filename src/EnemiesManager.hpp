#ifndef ENEMIESMANAGER_DB
#define ENEMIESMANAGER_DB

#include <set>
#include "Enemy.hpp"
#include "types.hpp"

class EnemiesManager
{
public:
	EnemiesManager ();
	void reset ();
	void update (float dt);
	void draw ();
	void spawn_EnemyBlock ();
	void set_difficulty (Difficulty newDifficulty);
	void update_EnemyBlock_settings ();
	
private:
	struct EnemyComparator
	{
		bool operator() (Enemy* e1, Enemy* e2) const
		{
			return e1->get_death_time() < e2->get_death_time();
		}
	};
	struct EnemyBlockSettings
	{
		/*	maximum possible number of EnemyBlock objects at the same time. */
		int maxCount = 4;
		/*	nextSpawnTime specifies at which point in time the manager will attempt to spawn a new EnemyBlock. */
		int nextSpawnTime;
		/*	nextSpawnTime takes the old value and increment it by a random number within the
			range of timeBounds */
		Range spawnTimeRange;
		Range widthRange, heightRange;
		Range maxVelocityRange;
		Range maxForceRange;
		Range lifespanRange;
	};
	EnemyBlockSettings EBS;
	std::set<Enemy*, EnemyComparator> enemies;
	Difficulty currentDifficulty;
};

#endif // ENEMIESMANAGER_DB