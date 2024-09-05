#include <ctime>
#include "raylib.h"
#include "misc_functions.h"
#include "game_objects.h"
#include "objects_manipulation_functions.h"
#include "buttons_initilizers.h"

////////////////// IMPORTANT VARIABLES //////////////////////////
char title[] = "DODGY BLOCKS";
float screenWidth, screenHeight;
short FPS = 60;
short numOfPlayers = 1;
bool  showFPS = 0;
bool  arcade = 1,            sandBox = 0;
bool  endGame = 0,           lostGame = 0;
/////////////////////////////////////////////////////////////////

////////////////////////////// METHODS DECLARATIONS ////////////////////////////
void setup_environment_and_resources ();

////// loops //////
void menu_loop ();
void gameSetup_loop ();
void settings_loop ();
void about_loop ();
void standard_game_loop ();
void pause_loop ();
void lostGame_loop ();

////// update //////
void update_menu ();
void update_gameSetup ();
void update_settings ();
void update_about ();
void update_standard_game (float dt);
void update_pause ();
void update_lostGame ();

////// draw //////
void draw_menu ();
void draw_gameSetup ();
void draw_settings ();
void draw_about ();
void draw_standard_game ();
void draw_pause ();
void draw_lostGame ();

//////////////////////// GAME RESOURCES ////////////////////////
timing timer ;
playerClass player[3];
gameEvents events;
backgroundClass background;
enemyManagementBlock blocksManager;

button menu_B[5];
button gameSetup_B[6];
button settings_B[16];
button about_B[1];
button pause_B[2];
button lostGame_B[1]; // initilized in initilize_pause_buttons

char gameSetupMsg1[] = "Number of players: ";
char gameSetupMsg2[] = "Game mode: ";

char settingsMsg1[] = "Select frame rate: ";
char settingsMsg2[] = "Show FPS: ";
char settingsMsg3[] = "Player 1 controls: ";
char settingsMsg4[] = "Player 2 controls: ";
char settingsMsg5[] = "Player 3 controls: ";

char aboutMsg1[] = "Made by Alaa Arees (PHOENIX) using Raylib library.";
char aboutMsg2[] = "Current version: 1.0";
char aboutMsg3[] = "this game is open source and built 100% in C++, if you want \nto check the source code or if you have any feedbacks \nfeel free to contact me on: \ndiscord or telegram phoenix_9226 (same username).";
char aboutMsg4[] = "Have a nice day!";

char lostGameMsg1[] = "Player 1 survived ";
char lostGameMsg2[] = "Player 2 survived ";
char lostGameMsg3[] = "Player 3 survived ";
////////////////////////////////////////////////////////////////

int main()
{
    setup_environment_and_resources ();
    menu_loop ();
    return 0;
}

////////////////////////////// FUNCTIONS DEFINITIONS ///////////////////////////////

void setup_environment_and_resources ()
{
    // new seed for random_number generator
    srand (time (NULL));
    
    // setup environment
    window_initilize (screenWidth, screenHeight);
    SetTargetFPS (FPS);
    
    // construct game objects
    timer.construct (screenWidth);
    
    player[0].construct (screenWidth, screenHeight);
    player[1].construct (screenWidth, screenHeight);
    player[2].construct (screenWidth, screenHeight);
    player[0].set_controls (0, {KEY_W, KEY_A, KEY_S, KEY_D});
    player[1].set_controls (0, {KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT});
    player[2].set_controls (1, {KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL});
    
    
    events.construct (&timer, player, &numOfPlayers, &endGame, &lostGame);
    
    blocksManager.construct (&events, screenWidth, screenHeight);
    
    background.construct (screenWidth, screenHeight);
    
    for (int i=0; i<4; i++)  {menu_B[i].construct (&background);}
    for (int i=0; i<6; i++)  {gameSetup_B[i].construct (&background);}
    for (int i=0; i<16; i++) {settings_B[i].construct (&background);}
    for (int i=0; i<1; i++)  {about_B[i].construct (&background);}
    for (int i=0; i<2; i++)  {pause_B[i].construct (&background);}
    for (int i=0; i<1; i++)  {lostGame_B[i].construct (&background);}
    
    // setup menus buttons
    initilize_menu_buttons (menu_B, screenWidth, screenHeight);
    initilize_gameSetup_buttons (gameSetup_B, screenWidth, screenHeight);
    initilize_settings_buttons (settings_B, screenWidth, screenHeight);
    initilize_about_buttons (about_B, screenWidth, screenHeight);
    initilize_pause_buttons (pause_B, lostGame_B, screenWidth, screenHeight);
}

//////////////////////////// FULL LOOPS ////////////////////////////////
void menu_loop ()
{
    background.initilize ();
    ClearBackground (WHITE);
    while (!menu_B[4].pressed)
    {
        update_menu ();
        
        if (menu_B[0].pressed || IsKeyPressed (KEY_ENTER)) {standard_game_loop ();}
        if (menu_B[1].pressed) {gameSetup_loop ();}
        if (menu_B[2].pressed) {settings_loop ();}
        if (menu_B[3].pressed) {about_loop ();}
        
        draw_menu ();
    }
}

void gameSetup_loop ()
{
    background.animate_recs ();
    
    ClearBackground (WHITE);
    while (!settings_B[5].pressed)
    {
        update_gameSetup ();
        
        if (gameSetup_B[0].pressed)  {numOfPlayers = 1;}
        if (gameSetup_B[1].pressed)  {numOfPlayers = 2;}
        if (gameSetup_B[2].pressed)  {numOfPlayers = 3;}
        if (gameSetup_B[3].pressed)  {arcade = 1; sandBox = 0;}
        if (gameSetup_B[4].pressed)  {arcade = 0; sandBox = 1;}
        
        draw_gameSetup ();
    }
    gameSetup_B[5].pressed = 0;
    background.animate_recs ();
}

void settings_loop ()
{
    background.animate_recs ();
    
    ClearBackground (WHITE);
    while (!settings_B[15].pressed)
    {
        update_settings ();
        
        if (settings_B[0].pressed)  {FPS = 30;     SetTargetFPS (FPS);}
        if (settings_B[1].pressed)  {FPS = 60;     SetTargetFPS (FPS);}
        if (settings_B[2].pressed)  {FPS = 90;     SetTargetFPS (FPS);}
        if (settings_B[3].pressed)  {FPS = 120;    SetTargetFPS (FPS);}
        if (settings_B[4].pressed)  {showFPS = 1;}
        if (settings_B[5].pressed)  {showFPS = 0;}
        
        // controls:
        if (settings_B[6].pressed)
        {player[0].set_and_swap_controls ({KEY_W, KEY_A, KEY_S, KEY_D}, player[1], player[2]);}
        if (settings_B[7].pressed)
        {player[0].set_and_swap_controls ({KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT}, player[1], player[2]);}
        if (settings_B[8].pressed)
        {player[0].set_and_swap_controls ({KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL}, player[1], player[2]);}
    
        if (settings_B[9].pressed)
        {player[1].set_and_swap_controls ({KEY_W, KEY_A, KEY_S, KEY_D}, player[0], player[2]);}
        if (settings_B[10].pressed)
        {player[1].set_and_swap_controls ({KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT}, player[0], player[2]);}
        if (settings_B[11].pressed)
        {player[1].set_and_swap_controls ({KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL}, player[0], player[2]);}
    
        if (settings_B[12].pressed)
        {player[2].set_and_swap_controls ({KEY_W, KEY_A, KEY_S, KEY_D}, player[0], player[1]);}
        if (settings_B[13].pressed)
        {player[2].set_and_swap_controls ({KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT}, player[0], player[1]);}
        if (settings_B[14].pressed)
        {player[2].set_and_swap_controls ({KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL}, player[0], player[1]);}
        
        draw_settings ();
    }
    settings_B[15].pressed = 0;
    background.animate_recs ();
}

void about_loop ()
{
    background.animate_recs ();
    
    ClearBackground (WHITE);
    while (!about_B[0].pressed)
    {
        update_about ();
        draw_about ();
    }
    about_B[0].pressed = 0;
    background.animate_recs ();
}

void pause_loop ()
{
    ClearBackground (GRAY);
    while (!pause_B[0].pressed)
    {
        update_pause ();
        draw_pause ();
        if (pause_B[1].pressed)
        {
            if (!player[0].isDead) {player[0].deathTime = timer.get_time ();}
            if (!player[1].isDead) {player[1].deathTime = timer.get_time ();}
            if (!player[2].isDead) {player[2].deathTime = timer.get_time ();}
            endGame = 1; return;
        }
    }
    pause_B[0].pressed = 0;
}

void lostGame_loop ()
{
    ClearBackground (GRAY);
    while (!lostGame_B[0].pressed && !IsKeyPressed (KEY_ENTER))
    {
        update_lostGame ();
        draw_lostGame ();
    }
    lostGame_B[0].pressed = 0;
}

void standard_game_loop ()
{
    ClearBackground (WHITE);
    background.initilize (); // to clear flying balls from the memory
    timer.reset ();
    blocksManager.reset ();
    
    player[0].spawn ();
    player[1].spawn ();
    player[2].spawn ();

    while (!endGame && !lostGame)
    {
        update_standard_game (GetFrameTime ());
        draw_standard_game ();
        if (WindowShouldClose ()) {pause_loop ();}
    }
    
    lostGame_loop ();
    
    endGame = 0;
    lostGame = 0;
    player[0].isDead = 0; player[1].isDead = 0; player[2].isDead = 0;
}

//////////////////////////// UPDATE METHODS ////////////////////////////
void update_menu ()
{
    background.update (GetFrameTime ());
    for (int i=0; i<5; i++) {menu_B[i].update ();}
}

void update_gameSetup ()
{
    background.update (GetFrameTime ());
    for (int i=0; i<6; i++) {settings_B[i].update ();}
}

void update_settings ()
{
    background.update (GetFrameTime ());
    for (int i=0; i<16; i++) {settings_B[i].update ();}
}

void update_about ()
{
    background.update (GetFrameTime ());
    for (int i=0; i<1; i++) {about_B[i].update ();}
}

void update_pause ()
{
    for (int i=0; i<2; i++) {pause_B[i].update ();}
}

void update_lostGame ()
{
    for (int i=0; i<1; i++) {lostGame_B[i].update ();}
}

void update_standard_game (float dt)
{
    if (!player[0].isDead) {player[0].update (dt);}
    if (!player[1].isDead && numOfPlayers > 1) {player[1].update (dt);}
    if (!player[2].isDead && numOfPlayers > 2) {player[2].update (dt);}
    timer.update(dt);
    
    // only in arcade mode:
    if (arcade) {blocksManager.update (dt);}
    if ((1 == numOfPlayers && player[0].isDead)
       || (2 == numOfPlayers && player[0].isDead && player[1].isDead)
       || (3 == numOfPlayers  && player[0].isDead && player[1].isDead && player[2].isDead))
    {lostGame = 1;}
}

////////////////////////////////////////////////////////////////////////

////////////////////////////  DRAW METHODS /////////////////////////////
void draw_menu ()
{
    BeginDrawing ();//////
    
    background.draw ();
    DrawText (title, screenWidth/2 - MeasureText (title, 70)/2, 100, 70, RED);
    for (int i=0; i<5; i++) {menu_B[i].draw ();}
    
    ClearBackground (WHITE);
    EndDrawing (); //////
}

void draw_gameSetup ()
{
    if (1 == numOfPlayers) {gameSetup_B[0].change_colors (1);}
    if (2 == numOfPlayers) {gameSetup_B[1].change_colors (1);}
    if (3 == numOfPlayers) {gameSetup_B[2].change_colors (1);}
    if (arcade)            {gameSetup_B[3].change_colors (1);}
    else                   {gameSetup_B[4].change_colors (1);}
    
    BeginDrawing (); //////
    
    for (int i=0; i<6; i++) {gameSetup_B[i].draw ();}
    draw_aligned_msg (gameSetupMsg1, gameSetup_B[0], ORANGE);
    draw_aligned_msg (gameSetupMsg2, gameSetup_B[3], ORANGE);
    
    ClearBackground (WHITE);
    EndDrawing (); //////
}

void draw_settings ()
{
    if (30 == FPS)      {settings_B[0].change_colors (1);}
    if (60 == FPS)      {settings_B[1].change_colors (1);}
    if (90 == FPS)      {settings_B[2].change_colors (1);}
    if (120 == FPS)     {settings_B[3].change_colors (1);}
    
    if (showFPS)        {settings_B[4].change_colors (1);}
    else                {settings_B[5].change_colors (1);}
    
    if (player[0].same_controls (KEY_W))   {settings_B[6].change_colors (1);}
    if (player[0].same_controls (KEY_UP))   {settings_B[7].change_colors (1);}
    if (player[0].same_controls (KEY_NULL))   {settings_B[8].change_colors (1);}
    
    if (player[1].same_controls (KEY_W))   {settings_B[9].change_colors (1);}
    if (player[1].same_controls (KEY_UP))   {settings_B[10].change_colors (1);}
    if (player[1].same_controls (KEY_NULL))   {settings_B[11].change_colors (1);}
    
    if (player[2].same_controls (KEY_W))   {settings_B[12].change_colors (1);}
    if (player[2].same_controls (KEY_UP))   {settings_B[13].change_colors (1);}
    if (player[2].same_controls (KEY_NULL))   {settings_B[14].change_colors (1);}
    
    BeginDrawing (); //////
    
    background.draw ();
    
    for (int i=0; i<16; i++) {settings_B[i].draw ();}
    
    draw_aligned_msg (settingsMsg1, settings_B[0], ORANGE);
    draw_aligned_msg (settingsMsg2, settings_B[4], ORANGE);
    draw_aligned_msg (settingsMsg3, settings_B[6], ORANGE);
    draw_aligned_msg (settingsMsg4, settings_B[9], ORANGE);
    draw_aligned_msg (settingsMsg5, settings_B[12], ORANGE);
    
    ClearBackground (WHITE);
    EndDrawing (); //////
}

void draw_about ()
{
    BeginDrawing (); //////
    
    background.draw ();
    for (int i=0; i<1; i++) {about_B[i].draw ();}
    DrawText (title, screenWidth/2 - MeasureText (title, 70)/2, 100, 70, RED);
    DrawText (aboutMsg1, screenWidth/16, 200, 30, ORANGE);
    DrawText (aboutMsg2, screenWidth/16, 250, 30, ORANGE);
    DrawText (aboutMsg3, screenWidth/16, 300, 30, ORANGE);
    DrawText (aboutMsg4, screenWidth/16, 500, 30, ORANGE);
    
    ClearBackground (WHITE);
    EndDrawing (); //////
}

void draw_pause ()
{
    BeginDrawing ();
    for (int i=0; i<2; i++) {pause_B[i].draw ();}
    ClearBackground (GRAY);
    EndDrawing ();
}

void draw_lostGame ()
{
    int temp;
    
    BeginDrawing ();
    for (int i=0; i<1; i++) {lostGame_B[i].draw ();}
    
    // player 1
    DrawText (lostGameMsg1, screenWidth/6, screenHeight/4, 50, YELLOW);
    temp = screenWidth/6 + MeasureText (lostGameMsg1, 50);
    DrawText (TextFormat ("%i", player[0].deathTime), temp, screenHeight/4, 50, YELLOW);
    temp += MeasureText (TextFormat ("%i", player[0].deathTime), 50);
    DrawText (" seconds", temp, screenHeight/4, 50, YELLOW);
    
    // player 2
    if (numOfPlayers > 1){
    DrawText (lostGameMsg2, screenWidth/6, screenHeight/4 + 100, 50, YELLOW);
    temp = screenWidth/6 + MeasureText (lostGameMsg2, 50);
    DrawText (TextFormat ("%i", player[1].deathTime), temp, screenHeight/4 + 100, 50, YELLOW);
    temp += MeasureText (TextFormat ("%i", player[1].deathTime), 50);
    DrawText (" seconds", temp, screenHeight/4 + 100, 50, YELLOW);
    }
    
    // player 3
    if (numOfPlayers > 2){
    DrawText (lostGameMsg2, screenWidth/6, screenHeight/4 + 200, 50, YELLOW);
    temp = screenWidth/6 + MeasureText (lostGameMsg2, 50);
    DrawText (TextFormat ("%i", player[2].deathTime), temp, screenHeight/4 + 200, 50, YELLOW);
    temp += MeasureText (TextFormat ("%i", player[2].deathTime), 50);
    DrawText (" seconds", temp, screenHeight/4 + 200, 50, YELLOW);
    }
    
    ClearBackground (GRAY);
    EndDrawing ();
}

void draw_standard_game ()
{
    BeginDrawing ();
    
    if (!player[0].isDead) {player[0].draw (RED);}
    if (!player[1].isDead && numOfPlayers > 1) {player[1].draw (BLUE);}
    if (!player[2].isDead && numOfPlayers > 2) {player[2].draw (GREEN);}
    if (showFPS) {DrawFPS (20, 20);}
    timer.draw();
    
    // only in arcade mode:
    if (arcade) {blocksManager.draw ();}
    
    ClearBackground (WHITE);
    EndDrawing ();
}


/////////////////////////////////////////////////////////////////////////