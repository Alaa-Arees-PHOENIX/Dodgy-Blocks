#include "raylib.h"
#include "DB_global_variables.h"
#include "DB_UI_resources.h"
#include "DB_game_loops.h"

////////////////////////////// FUNCTIONS DECLARATIONS ////////////////////////////
void draw_message_aligned (button, char[], Color);

////// loops //////
void menu_loop ();
void settings_loop ();
void about_loop ();

////// update //////
void update_buttons (button[], short);

////// draw //////
void draw_menu ();
void draw_settings ();
void draw_about ();
////////////////////////////////////////////////////////////////

////////////////////////////// FUNCTIONS DEFINITIONS ////////////////////////////
void draw_message_aligned (button B, char msg[], Color color)
{
    float tempSize, temp_x;
    tempSize = B.get_size () + 15;
    temp_x = B.get_x() - MeasureText (msg, tempSize) - 50;
    DrawText (msg, temp_x, B.get_y (), tempSize, color);
}

//////////////////////////// FULL LOOPS ////////////////////////////////
void menu_loop ()
{
    backgroundObj.initilize ();
    ClearBackground (GRAY);
    while (!menu_B[3].isPressed ())
    {
        update_buttons (menu_B, menuButtonsCount);
        
        if (menu_B[0].isPressed () || IsKeyPressed (KEY_ENTER)) {standard_game_loop ();}
        if (menu_B[1].isPressed ()) {settings_loop ();}
        if (menu_B[2].isPressed ()) {about_loop ();}
        
        draw_menu ();
    }
}

void settings_loop ()
{
    backgroundObj.animate_recs ();
    
    ClearBackground (GRAY);
    while (!settings_B[10].isPressed ())
    {
        update_buttons (settings_B, settingsButtonsCount);
        
        if (settings_B[0].isPressed ())  {FPS = 30;          SetTargetFPS (FPS);}
        if (settings_B[1].isPressed ())  {FPS = 60;          SetTargetFPS (FPS);}
        if (settings_B[2].isPressed ())  {FPS = 90;          SetTargetFPS (FPS);}
        if (settings_B[3].isPressed ())  {FPS = 120;         SetTargetFPS (FPS);}
        if (settings_B[4].isPressed ())  {showFPS = 1;       hideFPS = 0;}
        if (settings_B[5].isPressed ())  {showFPS = 0;       hideFPS = 1;}
        if (settings_B[6].isPressed ())  {singlePlayer = 1;  multiPlayer = 0;}
        if (settings_B[7].isPressed ())  {singlePlayer = 0;  multiPlayer = 1;}
        if (settings_B[8].isPressed ())  {arcade = 1;        sandBox = 0;}
        if (settings_B[9].isPressed ())  {arcade = 0;        sandBox = 1;}
        
        draw_settings ();
    }
    settings_B[10].release ();
    backgroundObj.animate_recs ();
}

void about_loop ()
{
    backgroundObj.animate_recs ();
    
    ClearBackground (GRAY);
    while (!about_B[0].isPressed ())
    {
        update_buttons (about_B, aboutButtonsCount);
        draw_about ();
    }
    about_B[0].release ();
    backgroundObj.animate_recs ();
}

//////////////////////////// UPDATE METHODS ////////////////////////////
void update_buttons (button arr[], short size)
{
    for (short i=0; i<size; i++) {arr[i].update ();}
    backgroundObj.update (GetFrameTime ());
}

////////////////////////////  DRAW METHODS /////////////////////////////
void draw_menu ()
{
    BeginDrawing ();
    
    backgroundObj.draw ();
    DrawText (title, screenWidth/2 - MeasureText (title, 70)/2, 100, 70, RED);
    for (short i=0; i<menuButtonsCount; i++) {menu_B[i].draw ();}
    
    ClearBackground (WHITE);
    EndDrawing ();
}

void draw_settings ()
{
    if (30 == FPS)      {settings_B[0].activate (); settings_B[0].change_colors ();}
    if (60 == FPS)      {settings_B[1].activate (); settings_B[1].change_colors ();}
    if (90 == FPS)      {settings_B[2].activate (); settings_B[2].change_colors ();}
    if (120 == FPS)     {settings_B[3].activate (); settings_B[3].change_colors ();}
    if (showFPS)        {settings_B[4].activate (); settings_B[4].change_colors ();}
    else                {settings_B[5].activate (); settings_B[5].change_colors ();}
    if (singlePlayer)   {settings_B[6].activate (); settings_B[6].change_colors ();}
    else                {settings_B[7].activate (); settings_B[7].change_colors ();}
    if (arcade)         {settings_B[8].activate (); settings_B[8].change_colors ();}
    else                {settings_B[9].activate (); settings_B[9].change_colors ();}
    
    BeginDrawing ();
    
    backgroundObj.draw ();
    
    // draw buttons:
    for (short i=0; i<settingsButtonsCount; i++) {settings_B[i].draw ();}
    
    // draw messages:
    draw_message_aligned (settings_B[0], settingsMsg1, ORANGE);
    draw_message_aligned (settings_B[4], settingsMsg2, ORANGE);
    draw_message_aligned (settings_B[6], settingsMsg3, ORANGE);
    draw_message_aligned (settings_B[8], settingsMsg4, ORANGE);
    
    ClearBackground (WHITE);
    EndDrawing ();
}

void draw_about ()
{
    BeginDrawing ();
    
    backgroundObj.draw ();
    for (short i=0; i<aboutButtonsCount; i++) {about_B[i].draw ();}
    DrawText (title, screenWidth/2 - MeasureText (title, 70)/2, 100, 70, RED);
    DrawText (aboutMsg1, screenWidth/16, 200, 30, ORANGE);
    DrawText (aboutMsg2, screenWidth/16, 250, 30, ORANGE);
    DrawText (aboutMsg3, screenWidth/16, 300, 30, ORANGE);
    DrawText (aboutMsg4, screenWidth/16, 500, 30, ORANGE);
    
    ClearBackground (WHITE);
    EndDrawing ();
}

////////////////////////////////////////////////////////////////