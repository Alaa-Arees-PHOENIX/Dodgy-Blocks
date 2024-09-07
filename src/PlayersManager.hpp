#ifndef PLAYERSMANAGER_DB
#define PLAYERSMANAGER_DB

#include "raylib.h"
#include "Player.hpp"

class EnemyBlock;

class PlayersManager
{
public:
	PlayersManager ();
	void collide_EnemyBlock_with_players (EnemyBlock& block);
	Player& pick_target_for_enemy (Vector2 enemyPosition);
	void update (float dt);
	void draw ();
	
	Player& P (size_t index) {return *p[index];}
	
private:
	Player* p[3];
};

#endif // PLAYERSMANAGER_DB