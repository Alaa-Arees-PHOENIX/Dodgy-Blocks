#ifndef UI_RESOURCES
#define UI_RESOURCES

#include "raylib.h"
#include "DB_global_variables.h"
#include "DB_misc_functions.h"
#include <string>
#include <cmath>
#include <vector>
#include <tuple>

////////////////////////////// CLASSES /////////////////////////////////////////
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
        void set_target ()
        {
            int x = random_number (0, screenWidth);
            int y = random_number (0, screenHeight);
            target = {(float)x, (float)y};
        }
        
        void initilize ()
        {
            float w = random_number (50, 200);
            float h = random_number (50, 200);
            body = {screenWidth/2, screenHeight/2, w, h};
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
    bool active = 0, pressed = 0;
    
    Color background, outlines, textColor;
    Color activeBackground, activeOutlines, activeTextColor; //when mouse hover over button
    Color currentBackground, currentOutlines, currentTextColor;
    
    public:
    
    void press () {pressed = 1;}
    void release () {pressed = 0;}
    bool isPressed () {return pressed;}
    
    void activate () {active = 1;}
    void disactivate () {active = 0;}
    bool isActive () {return active;}
    
    float get_x () {return bounds.x;}
    float get_y () {return bounds.y;}
    float get_width () {return bounds.width;}
    float get_size () {return textSize;}
    
    void initilize (std::tuple <Rectangle, std::string, int> basics, 
                    std::tuple <Color, Color, Color> normalColors = {BLACK, RED, WHITE}, 
                    std::tuple <Color, Color, Color> activeColors = {BLACK, GREEN, SKYBLUE})
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
        DrawRectangleRoundedLines ({bounds.x+1, bounds.y+1, bounds.width-2, bounds.height-2},
            0.8, 0, 10, currentOutlines);
    }
};
////////////////////////////////////////////////////////////////

//////////////////////// GAME RESOURCES ////////////////////////
const short menuButtonsCount = 4;         button menu_B [menuButtonsCount];
const short settingsButtonsCount = 11;    button settings_B [settingsButtonsCount];
const short aboutButtonsCount = 1;        button about_B [aboutButtonsCount];

// used inside "DB_game_loops.h" :
const short pauseButtonsCount = 2;        button pause_B [pauseButtonsCount];
const short lostGameButtonsCount = 1;     button lostGame_B[lostGameButtonsCount]; 

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

#endif