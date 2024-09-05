#ifndef TIMER_DB
#define TIMER_DB

#include "raylib.h"

class Timer
{
private:
    double currentTime;
    Rectangle bounds;
    int text_x, text_y;
    float textSize; // initilized in the constructor
	static constexpr float BASE_WIDTH = 74, BASE_HEIGHT = 22.2;
	
public:
	Timer ();
    void reset ();
    void update (float dt);
    void draw ();
	
public: // Functions intended to be inlined by the compiler:
    int get_time () {return (int)currentTime;}
};

#endif