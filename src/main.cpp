#include "raylib.h"
#include "DB_global_variables.h"
#include "DB_UI_resources.h"
#include "DB_UI_loops.h"
#include "DB_UI_initilizers.h"
#include "DB_game_objects.h"
#include <ctime>

////////////////// FUNCTIONS DECLARATIONS //////////////////////////
void window_initilize ();
/////////////////////////////////////////////////////////////////

int main ()
{
    // new seed for random_number generator
    srand (time (NULL));
    
    // setup environment
    window_initilize ();
    SetTargetFPS (FPS);
    
    // setup player
    p1.initilize ({KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT});
    p2.initilize ({KEY_W, KEY_A, KEY_S, KEY_D});
    
    // setup menus buttons
    initilize_menu_buttons ();
    initilize_settings_buttons ();
    initilize_about_pause_lostGame_buttons ();
    
    timer.construct ();
    
    menu_loop ();
    
    return 0;
}

////////////////////////////// FUNCTIONS DEFINITIONS ///////////////////////////////
void window_initilize ()
{
    InitWindow (0, 0, title);
    int monitor = GetCurrentMonitor ();
    screenWidth = GetMonitorWidth (monitor);
    screenHeight = GetMonitorHeight (monitor);
    SetWindowSize (screenWidth, screenHeight);
    ToggleFullscreen ();
}
/////////////////////////////////////////////////////////////////