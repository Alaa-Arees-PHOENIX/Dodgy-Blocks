#pragma once
#include "game_objects.h"

//////////////////////////// DECLARATIONS ////////////////////////////////////
void initilize_menu_buttons (button * menu_B, float screenWidth, float screenHeight);
void initilize_gameSetup_buttons (button * gameSetup_B, float screenWidth, float screenHeight);
void initilize_settings_buttons (button * settings_B, float screenWidth, float screenHeight);
void initilize_about_buttons (button * about_B, float screenWidth, float screenHeight);
void initilize_pause_buttons (button * pause_B, button * lostGame_B, float screenWidth, float screenHeight); // and lostGame_B[0]

//////////////////////////// DEFENITIONS /////////////////////////////////////
void initilize_menu_buttons (button * menu_B, float screenWidth, float screenHeight)
{ 
    std::tuple <Color, Color, Color> defaultNormalColors = {BLACK, RED, WHITE};
    std::tuple <Color, Color, Color> defaultActiveColors = {BLACK, GREEN, SKYBLUE};
    std::tuple <Rectangle, std::string, float> basics; //temp variable to help in construction process
    Rectangle rec; // also temp
    
    rec = {screenWidth/2 - 75, 200, 150, 40}; // x, y, width, height
    basics = {rec, "Play", 20}; //position, text, text size
    menu_B[0].initilize (basics, defaultNormalColors, defaultActiveColors);

    rec = {screenWidth/2 - 75, 300, 150, 40}; // y = B1.y + B1.height + 60 (to leave some space)
    basics = {rec, "Game setup", 20};
    menu_B[1].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 - 75, 400, 150, 40}; // y = B1.y + B1.height + 60 (to leave some space)
    basics = {rec, "Settings", 20};
    menu_B[2].initilize (basics, defaultNormalColors, defaultActiveColors);

    rec = {screenWidth/2 - 75, 500, 150, 40};
    basics = {rec, "About us", 20};
    menu_B[3].initilize (basics, defaultNormalColors, defaultActiveColors);

    rec = {screenWidth/2 - 75, 600, 150, 40};
    basics = {rec, "Quit game", 20};
    menu_B[4].initilize (basics, defaultNormalColors, defaultActiveColors);
}

void initilize_gameSetup_buttons (button * gameSetup_B, float screenWidth, float screenHeight)
{
    std::tuple <Color, Color, Color> defaultNormalColors = {BLACK, RED, WHITE};
    std::tuple <Color, Color, Color> defaultActiveColors = {BLACK, GREEN, SKYBLUE};
    std::tuple <Rectangle, std::string, float> basics;
    Rectangle rec;
    
    rec = {screenWidth/2 - 75, 150, 75, 40}; // x, y, width, height
    basics = {rec, "1", 20}; //position, text, text size
    gameSetup_B[0].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 + 25, 150, 75, 40};
    basics = {rec, "2", 20};
    gameSetup_B[1].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 + 125, 150, 75, 40};
    basics = {rec, "3", 20};
    gameSetup_B[2].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 - 75, 250, 150, 40};
    basics = {rec, "Arcade", 20};
    gameSetup_B[3].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 + 125, 250, 150, 40};
    basics = {rec, "Sand box", 20};
    gameSetup_B[4].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {3* screenWidth/4 + 30, 3* screenHeight/4 + 60, 150, 40};
    basics = {rec, "Main menu", 20};
    gameSetup_B[5].initilize (basics, defaultNormalColors, defaultActiveColors);
}

void initilize_settings_buttons (button * settings_B, float screenWidth, float screenHeight)
{
    std::tuple <Color, Color, Color> defaultNormalColors = {BLACK, RED, WHITE};
    std::tuple <Color, Color, Color> defaultActiveColors = {BLACK, GREEN, SKYBLUE};
    std::tuple <Rectangle, std::string, float> basics;
    Rectangle rec;
    
    rec = {screenWidth/2 - 75, 150, 75, 40}; // x, y, width, height
    basics = {rec, "30", 20}; //position, text, text size
    settings_B[0].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 + 25, 150, 75, 40};
    basics = {rec, "60", 20};
    settings_B[1].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 + 125, 150, 75, 40};
    basics = {rec, "90", 20};
    settings_B[2].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 + 225, 150, 75, 40};
    basics = {rec, "120", 20};
    settings_B[3].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 - 75, 250, 75, 40};
    basics = {rec, "On", 20};
    settings_B[4].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 + 25, 250, 75, 40};
    basics = {rec, "Off", 20};
    settings_B[5].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 - 75, 350, 150, 40};
    basics = {rec, "WASD", 20};
    settings_B[6].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 + 125, 350, 150, 40};
    basics = {rec, "Arrows", 20};
    settings_B[7].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 - 75, 350, 150, 40};
    basics = {rec, "Mouse", 20};
    settings_B[8].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 - 75, 450, 150, 40};
    basics = {rec, "WASD", 20};
    settings_B[9].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 + 125, 450, 150, 40};
    basics = {rec, "Arrows", 20};
    settings_B[10].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 - 75, 450, 150, 40};
    basics = {rec, "Mouse", 20};
    settings_B[11].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 - 75, 550, 150, 40};
    basics = {rec, "WASD", 20};
    settings_B[12].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 + 125, 550, 150, 40};
    basics = {rec, "Arrows", 20};
    settings_B[13].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {screenWidth/2 - 75, 550, 150, 40};
    basics = {rec, "Mouse", 20};
    settings_B[14].initilize (basics, defaultNormalColors, defaultActiveColors);
    
    rec = {3* screenWidth/4 + 30, 3* screenHeight/4 + 60, 150, 40};
    basics = {rec, "Main menu", 20};
    settings_B[15].initilize (basics, defaultNormalColors, defaultActiveColors);
}

void initilize_about_buttons (button * about_B, float screenWidth, float screenHeight)
{
    std::tuple <Color, Color, Color> defaultNormalColors = {BLACK, RED, WHITE};
    std::tuple <Color, Color, Color> defaultActiveColors = {BLACK, GREEN, SKYBLUE};
    std::tuple <Rectangle, std::string, float> basics;
    Rectangle rec;
    
    rec = {3* screenWidth/4 + 30, 3* screenHeight/4 + 60, 150, 40}; // x, y, width, height
    basics = {rec, "Main menu", 20}; //position, text, text size
    about_B[0].initilize (basics, defaultNormalColors, defaultActiveColors);
    
}

void initilize_pause_buttons (button * pause_B, button * lostGame_B, float screenWidth, float screenHeight)
{
    std::tuple <Color, Color, Color> defaultNormalColors = {BLACK, RED, WHITE};
    std::tuple <Color, Color, Color> defaultActiveColors = {BLACK, GREEN, SKYBLUE};
    std::tuple <Rectangle, std::string, float> basics;
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
