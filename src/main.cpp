#include <ctime>
#include <cmath>
#include <algorithm>
#include <string>
#include <tuple>
#include <deque>
#include <vector>
#include "raylib.h"

////////////////// IMPORTANT VARIABLES //////////////////////////
float screenWidth, screenHeight;
int FPS = 60;
char title[] = "DODGY BLOCKS";
int p1DiedAt, p2DiedAt; // how long each player have survived
const Color alphaBlack = {0, 0, 0, 150};
/////////////////////////////////////////////////////////////////

////////////////// IMPORTANT FUNCTIONS //////////////////////////
void window_initilize ();
int random_number (int, int);
double lerp (float, float, float); // search for "lerp functions"
bool inside_vertically (Vector2, Rectangle); // check if a point is vertically inside a rectangle
bool inside_horizontally (Vector2, Rectangle);
/////////////////////////////////////////////////////////////////

////////////////// BOOLEANS FOR SETTINGS ////////////////////////
bool showFPS = 0,           hideFPS = 1;
bool singlePlayer = 1,      multiPlayer = 0;
bool arcade = 1,            sandBox = 0;
bool menuLoopIsActive = 1,  settingsLoopIsActive = 0;
bool aboutLoopIsActive = 0, gameLoopIsActive = 0;
bool p1Died = 0, p2Died = 0; // when a player dies his variable becomes 1
bool endGame = 0, lostGame = 0;
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

class player
{
    private:
    float radius = 25;
    Vector2 position = {200, 200};
    Vector2 velocity = {0, 0};
    float acceleration = 3600;
    
    // controls:
    int UP, LEFT, DOWN, RIGHT;
    
    // assistant variables:
    bool limitUp, limitDown, limitLeft, limitRight;
    
    public:
    
    Vector2 get_position () {return position;}
    float get_x () {return position.x;}
    float get_y () {return position.y;}
    
    void initilize (std::tuple <int, int, int, int> controls)
    {
        std::tie (UP, LEFT, DOWN, RIGHT) = controls;
        position = {random_number (0 ,screenWidth), random_number (0, screenHeight)};
        velocity = {0, 0};
    }
    
    void bounce_on_edges(float dt)
    {
        // UO
        if (position.y - radius <= 0)
            {velocity.y = abs (velocity.y) + acceleration * dt;}
        // DOWN
        else if (position.y + radius >= screenHeight)
            {velocity.y = -abs (velocity.y) - acceleration * dt;}
        // LEFT
        if (position.x - radius <= 0)
            {velocity.x = abs (velocity.x) + acceleration * dt;}
        // RIGHT
        else if (position.x + radius >= screenWidth)
            {velocity.x = -abs (velocity.x) - acceleration * dt;}
    }
    
    void update (float dt)
    {
        //move up/down
        limitUp = (velocity.y > -1200 && position.y > 0);
        limitDown = (velocity.y < 1200 && position.y < screenHeight);
        
        if (IsKeyDown (UP) && limitUp)              {velocity.y -= acceleration * dt;}
        else if (IsKeyDown (DOWN) && limitDown)     {velocity.y += acceleration * dt;}
        else if (IsKeyUp (UP) && velocity.y < 0)    {velocity.y += acceleration * dt;}
        else if (IsKeyUp (DOWN) && velocity.y > 0)  {velocity.y -= acceleration * dt;}
        
        //move left/right
        limitLeft = (velocity.x > -1200 && position.x > 0);
        limitRight = (velocity.x < 1200 && position.x < screenWidth);
        
        if (IsKeyDown (LEFT) && limitLeft)          {velocity.x -= acceleration * dt;}
        else if (IsKeyDown (RIGHT) && limitRight)   {velocity.x += acceleration * dt;}
        else if (IsKeyUp (LEFT) && velocity.x < 0)  {velocity.x += acceleration * dt;}
        else if (IsKeyUp (RIGHT) && velocity.x > 0) {velocity.x -= acceleration * dt;}
        
        bounce_on_edges (dt);
        
        // fix floating point errors
        if (abs (velocity.x) * dt < 0.25f && IsKeyUp (LEFT) && IsKeyUp (RIGHT)) {velocity.x = 0;}
        if (abs (velocity.y) * dt < 0.25f && IsKeyUp (UP) && IsKeyUp (DOWN)) {velocity.y = 0;}
        
        // actual movement
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
    }
    
    void draw (Color c)
    {
        DrawCircle (position.x, position.y, radius, c);
    }
}p1, p2;

class singleEnemyBlock
{
    private:
    player target = p1;
    Vector2 velocity = {0, 0}, acceleration;
    Rectangle warningLeft, warningRight; // will draw a small rectangle on
                                    // the edges when the enemy is outside the screen
    Rectangle warningUp, warningDown;
    
    public:
    Rectangle body;
    int dieAtSecond; // object will deconstruct at this second
    
    singleEnemyBlock (Vector2 position)
    {
        float w = random_number (50, 150);
        float h = random_number (50, 150);
        body = {position.x, position.y, w, h};
        
        int max_x = 60, max_y = 40; // for game balance
        
        if (w*h > 10000) {max_x -= 10;}
        else if (w*h > 17500) {max_x -= 20; max_y -= 10;}
        
        acceleration.x = random_number (20, max_x); acceleration.x *= acceleration.x;
        acceleration.y = random_number (10, max_y); acceleration.y *= acceleration.y;
        dieAtSecond = timer.get_time () + random_number (7, 17);
        
        warningLeft = {0, 0, 15, h}; // same height with a small width,
                                     // pos on the y-axis doesn't matter it's variable
        warningRight = {screenWidth - 15, 0, 15, h};
        warningUp = {0, 0, w, 15};
        warningDown = {0, screenHeight - 15, w, 15};
    }
    
    void bounce_on_edges(float dt)
    {
        if (body.x <= 0)
            {velocity.x = abs (velocity.x) + acceleration.x * dt;}
        else if (body.x + body.width >= screenWidth)
            {velocity.x = -abs (velocity.x) - acceleration.x * dt;}
        
        if (body.y <= 0)
            {velocity.y = abs (velocity.y) + acceleration.y * dt;}
        else if (body.y + body.height >= screenHeight)
            {velocity.y = -abs (velocity.y) - acceleration.y * dt;}
    }
    
    player pick_target ()
    {
        float disFromP1, disFromP2;
        Vector2 posP1, posP2;
        posP1 = p1.get_position ();
        posP2 = p2.get_position ();
        disFromP1 = (body.x-posP1.x)*(body.x-posP1.x) + (body.y-posP1.y)*(body.y-posP1.y);
        disFromP2 = (body.x-posP2.x)*(body.x-posP2.x) + (body.y-posP2.y)*(body.y-posP2.y);
        
        if ((disFromP1 < disFromP2 && !p1Died) || p2Died) {return p1;}
        else if (!p2Died) {return p2;}
    }
    
    void update (float dt)
    {
        if (multiPlayer) {target = pick_target ();} // choose to follow player 1 or 2
        else {target = p1;}
        
        /////////////
        if (body.y > target.get_y() && velocity.y > -1500)
            {velocity.y -= acceleration.y * dt;}
        else if (body.y < target.get_y() && velocity.y < 1500)
            {velocity.y += acceleration.y * dt;}
        
        if (body.x > target.get_x() && velocity.x > -1500)
            {velocity.x -= acceleration.x * dt;}
        else if (body.x < target.get_x() && velocity.x < 1500)
            {velocity.x += acceleration.x * dt;}
        /////////////
        
        // friction
        velocity.x *= 0.991;
        velocity.y *= 0.991;
        
        // actual movement
        body.x += velocity.x * dt;
        body.y += velocity.y * dt;
        
        // check if the enemy hits a player
        if (CheckCollisionCircleRec (p1.get_position (), 25, body) && !p1Died)
        {
            p1Died = 1;
            p1DiedAt = timer.get_time ();
        }
    
        else if (multiPlayer && CheckCollisionCircleRec (p2.get_position (), 25, body)
                 && !p2Died)
        {
            p2Died = 1;
            p2DiedAt = timer.get_time ();
        }
    }
    
    void draw ()
    {
        DrawRectangleRec (body, BLACK);
        
        // check and draw a warning sign if the enemy is outside the screen:
        
        warningLeft.y = body.y;
        warningRight.y = body.y;
        warningUp.x = body.x;
        warningDown.x = body.x;
        
        if (body.x + body.width < 0)
            {DrawRectangleRec (warningLeft, alphaBlack);}
        
        if (body.x > screenWidth)
            {DrawRectangleRec (warningRight, alphaBlack);}
        
        if (body.y < 0)
            {DrawRectangleRec (warningUp, alphaBlack);}
        
        if (body.y + body.height > screenHeight)
            {DrawRectangleRec (warningDown, alphaBlack);}
    }
};

bool compare_two_blocks (const singleEnemyBlock& b1, const singleEnemyBlock& b2)
{
    return b1.dieAtSecond < b2.dieAtSecond;
}

class managerEnemyBlock
{
    private:
    std::deque <singleEnemyBlock> enemiesList;
    int nextSpawnAt = 3; // which second in time
    
    public:
    
    void reset ()
    {
        enemiesList.clear ();
        nextSpawnAt = 3;
    }
    
    void spawn ()
    {
        float x = 0, y = 0;
        int whichSideToSpawnFrom = random_number (1, 4);
        switch (whichSideToSpawnFrom)
        {
            case 1: // up
                x = random_number (0, screenWidth);
                y = -250;
                break;
            case 2: // down
                x = random_number (0, screenWidth);
                y = screenHeight + 250;
                break;
            case 3: // left
                x = -250;
                y = random_number (0, screenHeight);
                break;
            case 4: // right
                x = screenWidth + 250;
                y = random_number (0, screenHeight);
                break;
        }
        enemiesList.push_back(singleEnemyBlock ({x, y}));
    }
    
    void update (float dt)
    {
        if (timer.get_time () >= nextSpawnAt && enemiesList.size () < 4)
        {
            spawn ();
            nextSpawnAt += random_number (3, 6);
        }
        
        if (enemiesList.empty ()) {return;}
        
        std::sort (enemiesList.begin(), enemiesList.end(), compare_two_blocks);
        while (timer.get_time () >= enemiesList.front ().dieAtSecond)
        {
            enemiesList.pop_front ();
            if (enemiesList.empty ()) {return;}
        }
        
        for (auto it = enemiesList.begin(); it != enemiesList.end (); it++)
        {
            it -> update (dt);
        }
    }
    void draw ()
    {
        if (enemiesList.empty ()) {return;}
        for (auto it = enemiesList.begin(); it != enemiesList.end (); it++)
        {
            it -> draw ();
        }
    }
}blocksManager;

class backgroundClass
{
    private:
    
    class floatingRectangle
    {
        private:
        Rectangle body;
        Vector2 target;
        float lerpSpeed, exponential; // assistant variables for update ()
        
        public:
        Vector2 upperLeft, upperRight, lowerLeft, lowerRight; // corner points of the rectangle
        
        void set_target ()
        {
            int x = random_number (0, screenWidth);
            int y = random_number (0, screenHeight);
            target = {x, y};
        }
        
        void initilize ()
        {
            float w = random_number (50, 200);
            float h = random_number (50, 200);
            body = {screenWidth/2, screenHeight/2, w, h};
            
            upperLeft = {body.x, body.y};
            upperRight = {body.x + body.width, body.y};
            lowerLeft = {body.x, body.y + body.height};
            lowerRight = {body.x + body.width, body.y + body.height};
            
            set_target ();
        }
        
        void update (float dt)
        {
            lerpSpeed = random_number (1, 9) / 10.0;
            exponential = pow (lerpSpeed, dt * lerpSpeed);
            body.x = lerp (target.x, body.x, exponential);
            body.y = lerp (target.y, body.y, exponential);
            
            // update corners
            upperLeft = {body.x, body.y};
            upperRight = {body.x + body.width, body.y};
            lowerLeft = {body.x, body.y + body.height};
            lowerRight = {body.x + body.width, body.y + body.height};
        }
        
        void draw ()
        {
            DrawRectangleRec (body, BLACK);
        }
        
    };
    
    class flyBall
    {
        private:
        int radius;
        Vector2 position, velocity, acceleration;
        
        // assistant variables:
        bool limitDown;
        
        public:
        
        flyBall ()
        {
            // pick radius and position:
            radius = random_number (5, 30);
            
            float x = 0, y = 0;
            int whichSideToSpawnFrom = random_number (1, 2);
            switch (whichSideToSpawnFrom)
            {
                case 1: // left
                    x = -radius;
                    y = random_number (0, screenHeight - 2*radius);
                    break;
                case 2: // right
                    x = screenWidth + radius;
                    y = random_number (0, screenHeight - 2*radius);
                    break;
            }
            position = {x, y};
            
            // movement variables:
            velocity.x = random_number (600, 2000);
            velocity.y = random_number (-1800, 0);
            acceleration.x = 100;
            acceleration.y = 3600; // gravity
        }
        
        int get_radius () {return radius;}
        Vector2 get_position () {return position;}
        Vector2 get_velocity () {return velocity;}
        
        void bounce_up () {velocity.y = abs (velocity.y);}
        void bounce_down (float dt)
        {
            velocity.y = -abs (velocity.y);
            if (abs (velocity.y) <= acceleration.y * dt) {velocity.y = 0;}
            else {velocity.y += acceleration.y * dt;} // v is negative, it will lose energy here
        }
        void bounce_left () {velocity.x = abs (velocity.x);}
        void bounce_right () {velocity.x = -abs (velocity.x);}
        
        void bounce_on_edges (float dt)
        {
            if (position.y + radius >= screenHeight) {bounce_down (dt);}
            if (position.x - radius <= 0)            {bounce_left ();}
            if (position.x + radius >= screenWidth)  {bounce_right ();}
        }
        
        void update (float dt)
        {
            //move up/down
            limitDown = (velocity.y < 2100 && position.y + radius < screenHeight);
            if (velocity.y < 0)                 {velocity.y += acceleration.y * dt;}
            if (velocity.y > 0 && limitDown)    {velocity.y += acceleration.y * dt;}
            
            // friction
            velocity.x *= 0.99;
            velocity.y *= 0.99;
            
            bounce_on_edges (dt);
            
            // actual movement
            position.x += velocity.x * dt;
            position.y += velocity.y * dt;
        }
        
        void draw ()
        {
            DrawCircle (position.x, position.y, radius, BLACK);
        }
    };
    
    floatingRectangle floatingRecs[10];
    short numOfFloatingRecs = 0;
    std::vector <flyBall> flyBalls;
    
    public:
    
    void initilize ()
    {
        numOfFloatingRecs = random_number (3, 8);
        for (int i=0; i < numOfFloatingRecs; i++) {floatingRecs[i].initilize ();}
        
        // flying balls:
        flyBalls.clear ();
    }
    
    void launchBall ()
    {
        flyBalls.push_back (flyBall());
    }
    
    void animate_recs ()
    {
        for (int i=0; i < numOfFloatingRecs; i++) {floatingRecs[i].set_target ();}
    }
    
    void update (float dt)
    {
        for (int i=0; i < numOfFloatingRecs; i++) {floatingRecs[i].update (dt);}
        if (flyBalls.empty ()) {return;}
        for (auto it = flyBalls.begin (); it != flyBalls.end (); it++) {it -> update (dt);}
    }
    
    void draw ()
    {
        for (int i=0; i < numOfFloatingRecs; i++) {floatingRecs[i].draw ();}
        if (flyBalls.empty ()) {return;}
        for (auto it = flyBalls.begin(); it != flyBalls.end(); it++) {it -> draw ();}
    }

}backgroundObj;

class button
{
    private:
    Rectangle bounds;
    std::string text;
    int textSize, textWidth, text_x, text_y;
    
    Color background, outlines, textColor;
    Color activeBackground, activeOutlines, activeTextColor; //when mouse hover over button
    Color currentBackground, currentOutlines, currentTextColor;
    
    public:
    bool active = 0, pressed = 0;
    
    float get_x () {return bounds.x;}
    float get_y () {return bounds.y;}
    float get_width () {return bounds.width;}
    float get_size () {return textSize;}
    
    void initilize (std::tuple <Rectangle, std::string, int> basics, 
                    std::tuple <Color, Color, Color> normalColors, 
                    std::tuple <Color, Color, Color> activeColors)
    {
        std::tie (bounds, text, textSize) = basics;
        std::tie (background, outlines, textColor) = normalColors;
        std::tie (activeBackground, activeOutlines, activeTextColor) = activeColors;
        
        // text center alignment:
        textWidth = MeasureText (text.c_str(), textSize);
        text_x = bounds.x + bounds.width/2 - textWidth/2;
        text_y = bounds.y + bounds.height/2 -10;
    }
    
    void change_colors ()
    {
        if (active)
        {
            currentBackground = activeBackground;
            currentOutlines = activeOutlines;
            currentTextColor = activeTextColor;
        }
        else
        {
            currentBackground = background;
            currentOutlines = outlines;
            currentTextColor = textColor;
        }
    }
    
    void update ()
    {
        if (CheckCollisionPointRec (GetMousePosition (), bounds))
        {
            active = 1;
            change_colors ();
        }
        else
        {
            active = 0;
            change_colors ();
        }
        
        if (active && IsMouseButtonReleased (MOUSE_BUTTON_LEFT))
        {
            pressed = 1;
            backgroundObj.launchBall ();
        } else {pressed = 0;}
    }
    
    void draw ()
    {
        DrawRectangleRounded (bounds, 0.8, 0, currentBackground);
        DrawText (text.c_str(), text_x, text_y, textSize, currentTextColor);
        DrawRectangleRoundedLines ({bounds.x+1, bounds.y+1,
                bounds.width-2, bounds.height-2}, 0.8, 0, 10, currentOutlines);
    }
};

////////////////////////////// METHODS DECLARATIONS ////////////////////////////
////// loops //////
void menu_loop ();
void settings_loop ();
void about_loop ();
void standard_game_loop ();
void pause_loop ();
void lostGame_loop ();

////// update //////
void update_menu ();
void update_settings ();
void update_about ();
void update_standard_game (float dt);
void update_pause ();
void update_lostGame ();

////// draw //////
void draw_menu ();
void draw_settings ();
void draw_about ();
void draw_standard_game ();
void draw_pause ();
void draw_lostGame ();

////// initilizers methods (game resources) //////
void initilize_players ();
void initilize_menu_buttons ();
void initilize_settings_buttons ();
void initilize_about_buttons ();
void initilize_pause_buttons (); // and lostGame_B1

//////////////////////// GAME RESOURCES ////////////////////////
button menu_B[4];
button settings_B[11];
button about_B[1];
button pause_B[2];
button lostGame_B[1]; // initilized in initilize_pause_buttons

char settingsMsg1[] = "Select frame rate: ";
char settingsMsg2[] = "Show FPS: ";
char settingsMsg3[] = "Number of players: ";
char settingsMsg4[] = "Game mode: ";

char aboutMsg1[] = "Made by Alaa Arees (PHOENIX) using Raylib library.";
char aboutMsg2[] = "Current version: 1.0";
char aboutMsg3[] = "this game is open source and built 100% in C++, if you want \nto check the source code or if you have any feedbacks \nfeel free to contact me on: \ndiscord or telegram phoenix_9226 (same username).";
char aboutMsg4[] = "Have a nice day!";

char lostGameMsg1[] = "Player 1 survived ";
char lostGameMsg2[] = "Player 2 survived ";
////////////////////////////////////////////////////////////////

int main()
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
    initilize_about_buttons ();
    initilize_pause_buttons ();
    
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

double lerp (float initialPos, float targetPos, float lerpSpeed)
{
    return initialPos*(1-lerpSpeed) + targetPos*lerpSpeed;
}

int random_number (int Min, int Max)
{
    return rand () % (Max - Min +1) + Min;
}

bool inside_vertically (Vector2 point, Rectangle rectangle)
{
    return point.y >= rectangle.y && point.y <= rectangle.y + rectangle.height;
}

bool inside_horizontally (Vector2 point, Rectangle rectangle)
{
    return point.x >= rectangle.x && point.x <= rectangle.x + rectangle.width;
}

//////////////////////////// FULL LOOPS ////////////////////////////////
void menu_loop ()
{
    backgroundObj.initilize ();
    ClearBackground (GRAY);
    while (!menu_B[3].pressed)
    {
        update_menu ();
        
        if (menu_B[0].pressed || IsKeyPressed (KEY_ENTER)) {standard_game_loop ();}
        if (menu_B[1].pressed) {settings_loop ();}
        if (menu_B[2].pressed) {about_loop ();}
        
        draw_menu ();
    }
}

void settings_loop ()
{
    backgroundObj.animate_recs ();
    
    ClearBackground (GRAY);
    while (!settings_B[10].pressed)
    {
        update_settings ();
        
        if (settings_B[0].pressed)  {FPS = 30;          SetTargetFPS (FPS);}
        if (settings_B[1].pressed)  {FPS = 60;          SetTargetFPS (FPS);}
        if (settings_B[2].pressed)  {FPS = 90;          SetTargetFPS (FPS);}
        if (settings_B[3].pressed)  {FPS = 120;         SetTargetFPS (FPS);}
        if (settings_B[4].pressed)  {showFPS = 1;       hideFPS = 0;}
        if (settings_B[5].pressed)  {showFPS = 0;       hideFPS = 1;}
        if (settings_B[6].pressed)  {singlePlayer = 1;  multiPlayer = 0;}
        if (settings_B[7].pressed)  {singlePlayer = 0;  multiPlayer = 1;}
        if (settings_B[8].pressed)  {arcade = 1;        sandBox = 0;}
        if (settings_B[9].pressed)  {arcade = 0;        sandBox = 1;}
        
        draw_settings ();
    }
    settings_B[10].pressed = 0;
    backgroundObj.animate_recs ();
}

void about_loop ()
{
    backgroundObj.animate_recs ();
    
    ClearBackground (GRAY);
    while (!about_B[0].pressed)
    {
        update_about ();
        draw_about ();
    }
    about_B[0].pressed = 0;
    backgroundObj.animate_recs ();
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
            if (!p1Died) {p1DiedAt = timer.get_time ();}
            if (!p2Died) {p2DiedAt = timer.get_time ();}
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
    backgroundObj.initilize ();
}

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

//////////////////////////// UPDATE METHODS ////////////////////////////
void update_menu ()
{
    backgroundObj.update (GetFrameTime ());
    for (int i=0; i<4; i++) {menu_B[i].update ();}
}

void update_settings ()
{
    backgroundObj.update (GetFrameTime ());
    for (int i=0; i<11; i++) {settings_B[i].update ();}
}

void update_about ()
{
    backgroundObj.update (GetFrameTime ());
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
    if (!p1Died) {p1.update (dt);}
    if (!p2Died && multiPlayer) {p2.update (dt);}
    timer.update(dt);
    
    // only in arcade mode:
    if (arcade) {blocksManager.update (dt);}
    if ((singlePlayer && p1Died) || (multiPlayer && p1Died && p2Died)) {lostGame = 1;} 
}

////////////////////////////////////////////////////////////////////////

////////////////////////////  DRAW METHODS /////////////////////////////
void draw_menu ()
{
    BeginDrawing ();
    
    backgroundObj.draw ();
    DrawText (title, screenWidth/2 - MeasureText (title, 70)/2, 100, 70, RED);
    for (int i=0; i<4; i++) {menu_B[i].draw ();}
    
    ClearBackground (WHITE);
    EndDrawing ();
}

void draw_settings ()
{
    if (30 == FPS)      {settings_B[0].active = 1; settings_B[0].change_colors ();}
    if (60 == FPS)      {settings_B[1].active = 1; settings_B[1].change_colors ();}
    if (90 == FPS)      {settings_B[2].active = 1; settings_B[2].change_colors ();}
    if (120 == FPS)     {settings_B[3].active = 1; settings_B[3].change_colors ();}
    if (showFPS)        {settings_B[4].active = 1; settings_B[4].change_colors ();}
    else                {settings_B[5].active = 1; settings_B[5].change_colors ();}
    if (singlePlayer)   {settings_B[6].active = 1; settings_B[6].change_colors ();}
    else                {settings_B[7].active = 1; settings_B[7].change_colors ();}
    if (arcade)         {settings_B[8].active = 1; settings_B[8].change_colors ();}
    else                {settings_B[9].active = 1; settings_B[9].change_colors ();}
    
    BeginDrawing ();
    
    backgroundObj.draw ();
    // draw buttons:
    for (int i=0; i<11; i++) {settings_B[i].draw ();}
    
    // draw messages:
    float tempSize, temp_x;
    
    tempSize = settings_B[0].get_size () + 15;
    temp_x = settings_B[0].get_x() - MeasureText (settingsMsg1, tempSize) - 50;
    DrawText (settingsMsg1, temp_x, settings_B[0].get_y (), tempSize, ORANGE);
    
    tempSize = settings_B[4].get_size () + 15;
    temp_x = settings_B[4].get_x() - MeasureText (settingsMsg2, tempSize) - 50;
    DrawText (settingsMsg2, temp_x, settings_B[4].get_y (), tempSize, ORANGE);
    
    tempSize = settings_B[6].get_size () + 15;
    temp_x = settings_B[6].get_x() - MeasureText (settingsMsg3, tempSize) - 50;
    DrawText (settingsMsg3, temp_x, settings_B[6].get_y (), tempSize, ORANGE);
    
    tempSize = settings_B[8].get_size () + 15;
    temp_x = settings_B[8].get_x() - MeasureText (settingsMsg4, tempSize) - 50;
    DrawText (settingsMsg4, temp_x, settings_B[8].get_y (), tempSize, ORANGE);
    
    ClearBackground (WHITE);
    EndDrawing ();
}

void draw_about ()
{
    BeginDrawing ();
    
    backgroundObj.draw ();
    for (int i=0; i<1; i++) {about_B[i].draw ();}
    DrawText (title, screenWidth/2 - MeasureText (title, 70)/2, 100, 70, RED);
    DrawText (aboutMsg1, screenWidth/16, 200, 30, ORANGE);
    DrawText (aboutMsg2, screenWidth/16, 250, 30, ORANGE);
    DrawText (aboutMsg3, screenWidth/16, 300, 30, ORANGE);
    DrawText (aboutMsg4, screenWidth/16, 500, 30, ORANGE);
    
    ClearBackground (WHITE);
    EndDrawing ();
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

////////////////////////////////////////////////////////////////////////


//////////////////////////// INITILIZERS ///////////////////////////////
void initilize_menu_buttons ()
{
    std::tuple <Color, Color, Color> defaultNormalColors = {BLACK, RED, WHITE};
    std::tuple <Color, Color, Color> defaultActiveColors = {BLACK, GREEN, SKYBLUE};
    std::tuple <Rectangle, std::string, int> basics; //temp variable to help in construction process
    Rectangle rec; // also temp
    
    rec = {screenWidth/2 - 75, 250, 150, 40}; // x, y, width, height
    basics = {rec, "Play", 20}; //position, text, text size
    menu_B[0].initilize (basics, defaultNormalColors, defaultActiveColors);

    rec = {screenWidth/2 - 75, 350, 150, 40}; // y = B1.y + B1.height + 60 (to leave some space)
    basics = {rec, "Settings", 20};
    menu_B[1].initilize (basics, defaultNormalColors, defaultActiveColors);

    rec = {screenWidth/2 - 75, 450, 150, 40};
    basics = {rec, "About us", 20};
    menu_B[2].initilize (basics, defaultNormalColors, defaultActiveColors);

    rec = {screenWidth/2 - 75, 550, 150, 40};
    basics = {rec, "Quit game", 20};
    menu_B[3].initilize (basics, defaultNormalColors, defaultActiveColors);
}

void initilize_settings_buttons ()
{
    std::tuple <Color, Color, Color> defaultNormalColors = {BLACK, RED, WHITE};
    std::tuple <Color, Color, Color> defaultActiveColors = {BLACK, GREEN, SKYBLUE};
    std::tuple <Rectangle, std::string, int> basics;
    Rectangle rec;
    
    rec = {screenWidth/2 - 75, 250, 75, 40}; // x, y, width, height
    basics = {rec, "30", 20}; //position, text, text size
    settings_B[0].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 + 25, 250, 75, 40};
    basics = {rec, "60", 20};
    settings_B[1].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 + 125, 250, 75, 40};
    basics = {rec, "90", 20};
    settings_B[2].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 + 225, 250, 75, 40};
    basics = {rec, "120", 20};
    settings_B[3].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 - 75, 350, 75, 40};
    basics = {rec, "On", 20};
    settings_B[4].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 + 25, 350, 75, 40};
    basics = {rec, "Off", 20};
    settings_B[5].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 - 75, 450, 150, 40};
    basics = {rec, "Single player", 20};
    settings_B[6].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 + 125, 450, 150, 40};
    basics = {rec, "Multiplayer", 20};
    settings_B[7].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 - 75, 550, 150, 40};
    basics = {rec, "Arcade", 20};
    settings_B[8].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 + 125, 550, 150, 40};
    basics = {rec, "Sand box", 20};
    settings_B[9].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {3* screenWidth/4 + 30, 3* screenHeight/4 + 60, 150, 40};
    basics = {rec, "Main menu", 20};
    settings_B[10].initilize (basics, defaultNormalColors, defaultActiveColors);
}

void initilize_about_buttons ()
{
    std::tuple <Color, Color, Color> defaultNormalColors = {BLACK, RED, WHITE};
    std::tuple <Color, Color, Color> defaultActiveColors = {BLACK, GREEN, SKYBLUE};
    std::tuple <Rectangle, std::string, int> basics;
    Rectangle rec;
    
    rec = {3* screenWidth/4 + 30, 3* screenHeight/4 + 60, 150, 40}; // x, y, width, height
    basics = {rec, "Main menu", 20}; //position, text, text size
    about_B[0].initilize (basics, defaultNormalColors, defaultActiveColors);
    
}

void initilize_pause_buttons ()
{
    std::tuple <Color, Color, Color> defaultNormalColors = {BLACK, RED, WHITE};
    std::tuple <Color, Color, Color> defaultActiveColors = {BLACK, GREEN, SKYBLUE};
    std::tuple <Rectangle, std::string, int> basics;
    Rectangle rec;
    
    rec = {screenWidth/2 - 250, screenHeight/2, 150, 40}; // x, y, width, height
    basics = {rec, "Resume", 20}; //position, text, text size
    pause_B[0].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 + 100, screenHeight/2, 150, 40};
    basics = {rec, "Main menu", 20};
    pause_B[1].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    // related to lostGame menu
    rec = {screenWidth/2 - 75, 3* screenHeight/4, 150, 40};
    basics = {rec, "Continue", 20};
    lostGame_B[0].initilize (basics, defaultNormalColors, defaultActiveColors);
}


/////////////////////////////////////////////////////////////////////////