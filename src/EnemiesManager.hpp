#ifndef ENEMIESMANAGER_DB
#define ENEMIESMANAGER_DB

#include <set>
#include "Enemy.hpp"

class EnemiesManager
{
private:
	struct EnemyComparator
	{
		bool operator() (Enemy* e1, Enemy* e2) const
		{
			return e1->get_death_time() < e2->get_death_time();
		}
	};
	std::set<Enemy*, EnemyComparator> enemies;
	static constexpr int MAX_BLOCKS_COUNT = 4; // maximum possible number of EnemyBlock objects at the same time.
	int nextSpawnTimeForBlocks; // at which point in time the manager will attempt to spawn a new EnemyBlock.
	
	
public:
	EnemiesManager ();
	void reset ();
	void update (float dt);
	void draw ();
	void spawn_EnemyBlock ();
};

#endif // ENEMIESMANAGER_DB