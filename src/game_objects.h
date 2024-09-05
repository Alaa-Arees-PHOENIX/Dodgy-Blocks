#pragma once
#include <tuple>
#include <deque>
#include <vector>
#include <string>
#include "raylib.h"
#include "misc_functions.h"

const Color alphaBlack = {0, 0, 0, 150};

class timing
{
    private:
    double currentTime = 0;
    Rectangle bounds;
    float textWidth, text_x, text_y;
    
    public:
    int get_time () {return (int)currentTime;}
    
    void construct (float screenWidth)
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
};

class playerClass
{
    private:
    float radius = 25;
    Vector2 position = {200, 200};
    Vector2 velocity = {0, 0};
    float acceleration = 3600;
    float screenWidth, screenHeight;
    
    // controls:
    int UP, LEFT, DOWN, RIGHT;
    bool useMouse = 0;
    bool accelerateUp = 0, accelerateLeft = 0, accelerateDown = 0, accelerateRight = 0;
    
    // assistant variables:
    bool limitUp, limitLeft, limitDown, limitRight;
    
    public:
    int deathTime;
    bool isDead = 0;
    
    void construct (float w, float h)
    {
        screenWidth = w;
        screenHeight = h;
    }
    
    Vector2 get_position () {return position;}
    float get_x () {return position.x;}
    float get_y () {return position.y;}
    std::tuple <int, int, int, int> get_controls ()
    {
        if (useMouse) {return {KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL};}
        else {return {UP, LEFT, DOWN, RIGHT};}
    }
    
    void set_controls (bool mouse, std::tuple <int, int, int, int> controls)
    {
        useMouse = mouse;
        std::tie (UP, LEFT, DOWN, RIGHT) = controls;
    }
    
    void spawn ()
    {
        position = {random_number (0 ,screenWidth), random_number (0, screenHeight)};
        velocity = {0, 0};
    }
    
    bool same_controls (int firstKey) // only compare the UP key
    {
        return UP == firstKey; // if the first key is the same then they are the same
    }
    
    void swap_controls (playerClass otherPlayer)
    {
        std::tuple <int, int, int, int> controls = otherPlayer.get_controls ();
        if (KEY_NULL == std::get<0>(controls)) // other player uses mouse for movement
        {
            otherPlayer.set_controls (0, {UP, LEFT, DOWN, RIGHT});
            this-> set_controls (1, controls);
        }
        else if (KEY_NULL == UP) // this player uses mouse for movement
        {
            otherPlayer.set_controls (1, {UP, LEFT, DOWN, RIGHT});
            this-> set_controls (0, controls);
        }
        else // both use keys for movement
        {
            otherPlayer.set_controls (0, {UP, LEFT, DOWN, RIGHT});
            this-> set_controls (0, controls);
        }
    }
    
    void set_and_swap_controls (std::tuple <int, int, int, int> controls,
                                playerClass p2, playerClass p3)
    {
        if (p2.same_controls (std::get<0>(controls))) {this-> swap_controls (p2);}
        if (p3.same_controls (std::get<0>(controls))) {this-> swap_controls (p3);}
    }
    
    void bounce_on_edges(float dt)
    {
        // UP
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
    
    void update_movement_limiters ()
    {
        limitUp = (velocity.y > -1200 && position.y > 0);
        limitDown = (velocity.y < 1200 && position.y < screenHeight);
        
        limitLeft = (velocity.x > -1200 && position.x > 0);
        limitRight = (velocity.x < 1200 && position.x < screenWidth);
        
        if (useMouse)
        {
            if (position.y > GetMouseY () && limitUp) {accelerateUp = 1;}
            if (position.y < GetMouseY () && limitDown) {accelerateDown = 1;}
            
            if (position.x > GetMouseX () && limitLeft) {accelerateLeft = 1;}
            if (position.x < GetMouseX () && limitRight) {accelerateRight = 1;}
        }
        else // uses keyboard
        {
            if (IsKeyDown (UP) && limitUp)              {accelerateUp = 1;}
            else if (IsKeyDown (DOWN) && limitDown)     {accelerateDown = 1;}
            else if (IsKeyUp (UP) && velocity.y < 0)    {accelerateDown = 1;} // deaccelerate
            else if (IsKeyUp (DOWN) && velocity.y > 0)  {accelerateUp = 1;} // deaccelerate
            
            if (IsKeyDown (LEFT) && limitLeft)          {accelerateLeft = 1;}
            else if (IsKeyDown (RIGHT) && limitRight)   {accelerateRight = 1;}
            else if (IsKeyUp (LEFT) && velocity.x < 0)  {accelerateRight = 1;} // deaccelerate
            else if (IsKeyUp (RIGHT) && velocity.x > 0) {accelerateLeft = 1;} // deaccelerate
        }
    }
    
    void update (float dt)
    {
        update_movement_limiters ();
        
        if (accelerateUp)   {velocity.y -= acceleration * dt;}
        if (accelerateDown) {velocity.y += acceleration * dt;}
        
        if (accelerateLeft)  {velocity.x -= acceleration * dt;}
        if (accelerateRight) {velocity.x += acceleration * dt;}
        
        bounce_on_edges (dt);
        
        // fix floating point errors
        if (abs (velocity.x) * dt < 0.25f) {velocity.x = 0;}
        if (abs (velocity.y) * dt < 0.25f) {velocity.y = 0;}
        
        // actual movement
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        
        // reset movement limiters for the next update
        accelerateUp = 0;
        accelerateLeft = 0;
        accelerateDown = 0;
        accelerateRight = 0;
    }
    
    void draw (Color c)
    {
        DrawCircle (position.x, position.y, radius, c);
    }
};

struct gameEvents
{
    timing *timer;
    playerClass *player; // will point to the array containing all 3 players
    short *numOfPlayers;
    bool *endGame, *lostGame;
    
    void construct (timing*t, playerClass*p, short*n, bool*e, bool*l)
    {
        timer = t;
        player = p;
        numOfPlayers = n;
        endGame = e;
        lostGame = l;
    }
};

class singleEnemyBlock
{
    private:
    playerClass target; // enemy will follow this player
    Vector2 velocity = {0, 0}, acceleration;
    Rectangle warningLeft, warningRight; // will draw a small rectangle on
                                    // the edges when the enemy is outside the screen
    Rectangle warningUp, warningDown;
    gameEvents * events;
    float screenWidth, screenHeight;
    
    public:
    Rectangle body;
    int dieAtSecond; // object will deconstruct at this second
    
    singleEnemyBlock (Vector2 position, gameEvents * events, float w, float h)
    {
        this -> events = events;
        screenWidth = w;
        screenHeight = h;
        
        float width = random_number (50, 150);
        float height = random_number (50, 150);
        body = {position.x, position.y, width, height};
        
        float max_x = 60, max_y = 40; // for game balance
        
        if (w*h > 10000) {max_x -= 10;}
        else if (w*h > 17500) {max_x -= 20; max_y -= 10;}
        
        acceleration.x = random_number (20, max_x); acceleration.x *= acceleration.x;
        acceleration.y = random_number (10, max_y); acceleration.y *= acceleration.y;
        dieAtSecond = events->timer->get_time () + random_number (7, 17);
        
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
    
    playerClass pick_target ()
    {
        float disFromP1, disFromP2, disFromP3;
        Vector2 posP1, posP2, posP3;
        posP1 = (events->player)[0].get_position ();
        posP2 = (events->player)[1].get_position ();
        posP3 = (events->player)[2].get_position ();
        disFromP1 = (body.x-posP1.x)*(body.x-posP1.x) + (body.y-posP1.y)*(body.y-posP1.y);
        disFromP2 = (body.x-posP2.x)*(body.x-posP2.x) + (body.y-posP2.y)*(body.y-posP2.y);
        disFromP3 = (body.x-posP3.x)*(body.x-posP3.x) + (body.y-posP3.y)*(body.y-posP3.y);
        
        if (1 == *(events->numOfPlayers)
            || (disFromP1 < disFromP2 && disFromP1 < disFromP3 && !(events->player)[0].isDead))
        {return (events->player)[0];}
        
        else if (2 == *(events->numOfPlayers)
                 || (disFromP2 < disFromP3 && !(events->player)[1].isDead))
        {return (events->player)[1];}
        
        else
        {return (events->player)[2];}
    }
    
    void player_enemy_collision ()
    {
        if (CheckCollisionCircleRec ((events->player)[0].get_position (), 25, body)
            && !(events->player)[0].isDead)
        {
            (events->player)[0].isDead = 1;
            (events->player)[0].deathTime = events->timer->get_time ();
        }
        
        if (CheckCollisionCircleRec ((events->player)[1].get_position (), 25, body)
            && !(events->player)[1].isDead)
        {
            (events->player)[1].isDead = 1;
            (events->player)[1].deathTime = events->timer->get_time ();
        }
        
        if (CheckCollisionCircleRec ((events->player)[2].get_position (), 25, body)
            && !(events->player)[2].isDead)
        {
            (events->player)[2].isDead = 1;
            (events->player)[2].deathTime = events->timer->get_time ();
        }
    }
    
    void update (float dt)
    {
        target = pick_target ();
        
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
        player_enemy_collision ();
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

/*bool compare_two_blocks (const singleEnemyBlock& b1, const singleEnemyBlock& b2)
{
    return b1.dieAtSecond < b2.dieAtSecond;
}*/

class enemyManagementBlock
{
    private:
    std::deque <singleEnemyBlock> enemiesList;
    int nextSpawnAt = 3; // which second in time
    gameEvents * events;
    float screenWidth, screenHeight;
    
    public:
    
    void construct (gameEvents * events, float w, float h)
    {
        this -> events = events;
        screenWidth = w;
        screenHeight = h;
    }
    
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
        enemiesList.push_back(singleEnemyBlock ({x, y}, events, screenWidth, screenHeight));
    }
    
    void update (float dt)
    {
        if (events->timer->get_time () >= nextSpawnAt && enemiesList.size () < 4)
        {
            spawn ();
            nextSpawnAt += random_number (3, 6);
        }
        
        if (enemiesList.empty ()) {return;}
        
        std::sort (enemiesList.begin(), enemiesList.end(),
            [&] (const singleEnemyBlock &b1, const singleEnemyBlock &b2)
            {return b1.dieAtSecond < b2.dieAtSecond;});
        
        while (events->timer->get_time () >= enemiesList.front ().dieAtSecond)
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
};

class backgroundClass
{
    private:
    
    class floatingRectangle
    {
        private:
        float screenWidth, screenHeight;
        Rectangle body;
        Vector2 target;
        float lerpSpeed, exponential; // assistant variables for update ()
        
        public:
        
        void set_target ()
        {
            float x = random_number (0, screenWidth);
            float y = random_number (0, screenHeight);
            target = {x, y};
        }
        
        void initilize (float w, float h)
        {
            screenWidth = w;
            screenHeight = h;
            float width = random_number (50, 200);
            float height = random_number (50, 200);
            body = {screenWidth/2, screenHeight/2, width, height};
            set_target ();
        }
        
        void update (float dt)
        {
            lerpSpeed = random_number (1, 9) / 10.0;
            exponential = pow (lerpSpeed, dt * lerpSpeed);
            body.x = lerp (target.x, body.x, exponential);
            body.y = lerp (target.y, body.y, exponential);
        }
        
        void draw ()
        {
            DrawRectangleRec (body, BLACK);
        }
        
    };
    
    class flyBall
    {
        private:
        float screenWidth, screenHeight;
        int radius;
        Vector2 position, velocity, acceleration;
        
        // assistant variables:
        bool limitDown;
        
        public:
        
        flyBall (float w, float h)
        {
            // set environment width and height:
            screenWidth = w;
            screenHeight = h;
            
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
    
    float screenWidth, screenHeight;
    floatingRectangle floatingRecs[10];
    short numOfFloatingRecs = 0;
    std::vector <flyBall> flyBalls;
    
    public:
    
    void construct (float w, float h)
    {
        screenWidth = w;
        screenHeight = h;
    }
    
    void initilize ()
    {
        numOfFloatingRecs = random_number (3, 8);
        for (int i=0; i < numOfFloatingRecs; i++) {floatingRecs[i].initilize (screenWidth, screenHeight);}
        
        // flying balls:
        flyBalls.clear ();
    }
    
    void launchBall ()
    {
        flyBalls.push_back (flyBall(screenWidth, screenHeight));
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

};

class button
{
    private:
    backgroundClass * backgroundObj;
    
    Rectangle bounds;
    std::string text;
    float textSize, textWidth, text_x, text_y;
    
    Color background, outlines, textColor;
    Color activeBackground, activeOutlines, activeTextColor; //when mouse hover over button
    Color currentBackground, currentOutlines, currentTextColor;
    
    public:
    bool active = 0, pressed = 0;
    
    void construct (backgroundClass * backgroundObj)
    {
        this -> backgroundObj = backgroundObj;
    }
    
    float get_x () {return bounds.x;}
    float get_y () {return bounds.y;}
    float get_width () {return bounds.width;}
    float get_size () {return textSize;}
    
    void initilize (std::tuple <Rectangle, std::string, float> basics, 
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
    
    void change_colors (bool activate)
    {
        if (activate)
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
            change_colors (active);
        }
        else
        {
            active = 0;
            change_colors (active);
        }
        
        if (active && IsMouseButtonReleased (MOUSE_BUTTON_LEFT))
        {
            pressed = 1;
            backgroundObj -> launchBall ();
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


