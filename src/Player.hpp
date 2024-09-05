#ifndef PLAYER_DB
#define PLAYER_DB

#include <tuple>
#include <cmath>
#include "raylib.h"
#include "MotiveCreature.hpp"

class Player : public MotiveCreature
{
private: // variables
    float radius; // has a default value of 19 assigned in the constructor
	Color color;
	bool dead; // is the player dead.
	int survivedFor; // survival time since the game start, in seconds.
	
    // controls:
    KeyboardKey UP, DOWN, LEFT, RIGHT;
	
public:
	Player (Vector2 MAX_VELOCITY, Vector2 ACC_FORCE, float MASS, Color color);

    void update (float dt) override;
    void draw () override;
    void set_controls (std::tuple <KeyboardKey, KeyboardKey, KeyboardKey, KeyboardKey> controls);
	void initilize ();
	void kill ();
	
	bool is_dead () {return dead;}
	int survival_time () {return survivedFor;}
	int get_radius () {return radius;}
    
private:
    void bounce_on_edges (float dt);
};

#endif