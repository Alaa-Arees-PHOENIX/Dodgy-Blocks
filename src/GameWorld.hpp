#ifndef GAMEWORLD_DB
#define GAMEWORLD_DB

#include "raylib.h"

class GameWorld
{
private:
	bool gameIsRunning;
public:
	GameWorld ();
	
public: // loops:
	void loop ();
	void update (float dt);
	void draw ();
	void terminate ();
	
	// DEBUGGING STUFF:
private:
	void draw_debug ();
};

#endif // GAMEWORLD_DB