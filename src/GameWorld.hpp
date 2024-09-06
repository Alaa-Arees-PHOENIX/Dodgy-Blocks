#ifndef GAMEWORLD_DB
#define GAMEWORLD_DB

#include "raylib.h"
#include "Player.hpp"

class GameWorld
{
private:
	Player p1, p2;
	
public:
	GameWorld ();
	
public: // loops:
	void loop ();
	void update (float dt);
	void draw ();
	
	Player& P1 () {return p1;}
	Player& P2 () {return p2;}
	
	// DEBUGGING STUFF:
private:
	void draw_debug ();
};

#endif // GAMEWORLD_DB