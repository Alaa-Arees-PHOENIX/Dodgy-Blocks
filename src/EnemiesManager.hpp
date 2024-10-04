#ifndef ENEMIESMANAGER_DB
#define ENEMIESMANAGER_DB

#include <forward_list>
#include <memory>
#include "Enemy.hpp"
#include "types.hpp"
#include "Logger.hpp"

class EnemiesManager : public Logger::Listener
{
public:
	EnemiesManager ();
	virtual ~EnemiesManager ();
	void reset ();
	void update (float dt);
	void draw ();
	void spawn_EnemyBlock ();
	void set_difficulty (Difficulty newDifficulty);
	void set_gameMode (GameMode newGameMode);
	void update_EnemyBlock_settings ();
	void log_info (	int logTime,
					bool useDefaultLogFile = 1,
					const char* alternativeFile = "\0") override;
	std::string get_difficulty_string ();
	std::string get_game_mode_string ();
	
	Difficulty get_difficulty () {return currentDifficulty;}
	bool is_game_mode_set_to (GameMode gm) {return currentGameMode == gm;}
	
private:
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
	std::forward_list<std::unique_ptr<Enemy>> enemies;
	Difficulty currentDifficulty;
	GameMode currentGameMode;
};

#endif // ENEMIESMANAGER_DB