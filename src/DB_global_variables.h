#ifndef GLOBAL_VARS
#define GLOBAL_VARS

#include "raylib.h"

////////////////// IMPORTANT VARIABLES //////////////////////////
float screenWidth = 0, screenHeight = 0;
int FPS = 60;
char title[] = "DODGY BLOCKS";
int p1DiedAt, p2DiedAt; // how long each player have survived
const Color alphaBlack = {0, 0, 0, 150};
/////////////////////////////////////////////////////////////////

////////////////// BOOLEANS FOR SETTINGS ////////////////////////
bool showFPS = 0,           hideFPS = 1;
bool singlePlayer = 1,      multiPlayer = 0;
bool arcade = 1,            sandBox = 0;
bool menuLoopIsActive = 1,  settingsLoopIsActive = 0;
bool aboutLoopIsActive = 0, gameLoopIsActive = 0;
bool p1Died = 0,            p2Died = 0; // when a player dies his variable becomes 1
bool endGame = 0,           lostGame = 0;
/////////////////////////////////////////////////////////////////

class timing
{
    private:
    double currentTime = 0;
    Rectangle bounds;
    int textWidth, text_x, text_y;
    
    public:
    int get_time () {return (int)currentTime;}
    
    void construct ()
    {
        bounds = {screenWidth - 120, 20, 100, 30};
        text_y = bounds.y + bounds.height/2 -10;
    }
    
    void reset ()
    {
        currentTime = 0;
    }
    
    void update (float dt)
    {
        currentTime += dt;
        textWidth = MeasureText (TextFormat ("%i", (int)currentTime), 20);
        text_x = bounds.x + bounds.width/2 - textWidth/2;
        if (textWidth >= bounds.width + 10)
        {bounds.width += 10;}
    }
    
    void draw ()
    {
        DrawRectangleRounded (bounds, 0.8, 0, BLACK);
        DrawText (TextFormat ("%i", (int)currentTime), text_x, text_y, 20, WHITE);
        DrawRectangleRoundedLines ({bounds.x+1, bounds.y+1,
                bounds.width-2, bounds.height-2}, 0.8, 0, 10, GRAY);
    }
}timer;

#endif