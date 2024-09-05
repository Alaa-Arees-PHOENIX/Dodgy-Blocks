#ifndef GAME_OBJ
#define GAME_OBJ

#include "raylib.h"
#include "DB_global_variables.h"
#include "DB_misc_functions.h"
#include <tuple>
#include <deque>

////////////////////////////// CLASSES /////////////////////////////////////////
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
        position = {(float)random_number (0, screenWidth), (float)random_number (0, screenHeight)};
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
////////////////////////////////////////////////////////////////

#endif
