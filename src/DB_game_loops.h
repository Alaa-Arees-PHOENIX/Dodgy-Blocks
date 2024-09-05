#ifndef GAME_LOOPS
#define GAME_LOOPS

#include "DB_global_variables.h"
#include "DB_game_objects.h"
#include "DB_UI_resources.h"

////////////////////////////// FUNCTIONS DECLARATIONS ///////////////////////////////
void standard_game_loop ();
void pause_loop ();
void lostGame_loop ();

void update_standard_game (float);
void update_pause ();
void update_lostGame ();

void draw_standard_game ();
void draw_pause ();
void draw_lostGame ();
////////////////////////////////////////////////////////////////////////

////////////////////////////// FUNCTIONS DEFINITIONS ///////////////////////////////
//////////// loops ////////////////

void standard_game_loop ()
{
    ClearBackground (BLACK);
    timer.reset ();
    blocksManager.reset ();
    
    while (!endGame && !lostGame)
    {
        update_standard_game (GetFrameTime ());
        draw_standard_game ();
        if (WindowShouldClose ()) {pause_loop ();}
    }
    
    lostGame_loop ();
    
    endGame = 0;
    lostGame = 0;
    p1Died = 0; p2Died = 0;
    p1.initilize ({KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT});
    p2.initilize ({KEY_W, KEY_A, KEY_S, KEY_D});
}

void pause_loop ()
{
    ClearBackground (GRAY);
    while (!pause_B[0].isPressed ())
    {
        update_pause ();
        draw_pause ();
        if (pause_B[1].isPressed ())
        {
            if (!p1Died) {p1DiedAt = timer.get_time ();}
            if (!p2Died) {p2DiedAt = timer.get_time ();}
            endGame = 1; return;
        }
        
    }
    pause_B[0].release ();
}

void lostGame_loop ()
{
    ClearBackground (GRAY);
    while (!lostGame_B[0].isPressed () && !IsKeyPressed (KEY_ENTER))
    {
        update_lostGame ();
        draw_lostGame ();
    }
    lostGame_B[0].release ();
    backgroundObj.initilize ();
}

//////////// update ///////////////

void update_standard_game (float dt)
{
    if (!p1Died) {p1.update (dt);}
    if (!p2Died && multiPlayer) {p2.update (dt);}
    timer.update(dt);
    
    // only in arcade mode:
    if (arcade) {blocksManager.update (dt);}
    if ((singlePlayer && p1Died) || (multiPlayer && p1Died && p2Died)) {lostGame = 1;} 
}

void update_pause ()
{
    for (short i=0; i<pauseButtonsCount; i++) {pause_B[i].update ();}
}

void update_lostGame ()
{
    for (short i=0; i<lostGameButtonsCount; i++) {lostGame_B[i].update ();}
}

///////////// draw /////////////////

void draw_standard_game ()
{
    BeginDrawing ();
    
    if (!p1Died) {p1.draw (RED);}
    if (!p2Died && multiPlayer) {p2.draw (BLUE);}
    if (showFPS) {DrawFPS (20, 20);}
    timer.draw();
    
    // only in arcade mode:
    if (arcade) {blocksManager.draw ();}
    
    ClearBackground (WHITE);
    EndDrawing ();
}

void draw_pause ()
{
    BeginDrawing ();
    for (short i=0; i<pauseButtonsCount; i++) {pause_B[i].draw ();}
    ClearBackground (GRAY);
    EndDrawing ();
}

void draw_lostGame ()
{
    int temp;
    
    BeginDrawing ();
    for (short i=0; i<lostGameButtonsCount; i++) {lostGame_B[i].draw ();}
    
    // player 1
    DrawText (lostGameMsg1, screenWidth/6, screenHeight/4, 50, YELLOW);
    temp = screenWidth/6 + MeasureText (lostGameMsg1, 50);
    DrawText (TextFormat ("%i", p1DiedAt), temp, screenHeight/4, 50, YELLOW);
    temp += MeasureText (TextFormat ("%i", p1DiedAt), 50);
    DrawText (" seconds", temp, screenHeight/4, 50, YELLOW);
    
    // player 2
    if (multiPlayer){
    DrawText (lostGameMsg2, screenWidth/6, screenHeight/4 + 100, 50, YELLOW);
    temp = screenWidth/6 + MeasureText (lostGameMsg2, 50);
    DrawText (TextFormat ("%i", p2DiedAt), temp, screenHeight/4 + 100, 50, YELLOW);
    temp += MeasureText (TextFormat ("%i", p2DiedAt), 50);
    DrawText (" seconds", temp, screenHeight/4 + 100, 50, YELLOW);
    }
    
    ClearBackground (GRAY);
    EndDrawing ();
}

////////////////////////////////////////////////////////////////////////

#endif