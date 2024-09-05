#ifndef WORLD_DB
#define WORLD_DB

#include "raylib.h"
#include "Player.hpp"

class World
{
	private:
	Player &p1, &p2;
	// EnemiesSpawner enemiesSpawner;
	
	public:
	World ();
	
	public: // loops:
	void game_loop ();
	void game_update (float dt);
	void game_draw ();
	
	Player& P1 () {return p1;}
	Player& P2 () {return p2;}
	
	// DEBUGGING STUFF:
	private:
	// void update_debug ();
	void draw_debug ();
};

#endif // WORLD_DB