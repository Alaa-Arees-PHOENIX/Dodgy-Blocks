#ifndef PLAYER_DB
#define PLAYER_DB

#include <tuple>
#include <cmath>
#include "raylib.h"
#include "MotiveCreature.hpp"

class Player : public MotiveCreature
{
	
public:
	Player (Vector2 MAX_VELOCITY, Vector2 ACC_FORCE, float MASS, Color color);

    void update (float dt) override;
    void draw () override;
    void set_controls (std::tuple <KeyboardKey, KeyboardKey, KeyboardKey, KeyboardKey> controls);
	void initilize ();
	void kill ();
	
	bool is_dead () {return dead;}
	bool is_active () {return active;}
	void activate (bool b) {active = b;}
	int survival_time () {return survivedFor;}
	float get_radius () {return RADIUS;}
    
private:
    void bounce_on_edges (float dt);
	
private:
    static constexpr float RADIUS = 19;
	Color color;
	bool dead; // is the player dead.
	int survivedFor; // survival time since the game start, in seconds.
	bool active; // is the player active (for singleplayer and multiplayer mods), only toggled in SettingsMenu.
	
    // controls:
    KeyboardKey UP, DOWN, LEFT, RIGHT;
};

#endif