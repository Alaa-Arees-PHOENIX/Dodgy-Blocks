#include "DB_global_variables.h"
#include "DB_UI_resources.h"

//////////////////////////// INITILIZERS ///////////////////////////////
void initilize_menu_buttons ()
{
    Rectangle rec; // assistant variable
    
    rec = {screenWidth/2 - 75, 250, 150, 40}; // x, y, width, height
    menu_B[0].initilize ({rec, "Play", 20}); //position, text, text size

    rec = {screenWidth/2 - 75, 350, 150, 40}; // y = B1.y + B1.height + 60 (to leave some space)
    menu_B[1].initilize ({rec, "Settings", 20});

    rec = {screenWidth/2 - 75, 450, 150, 40};
    menu_B[2].initilize ({rec, "About us", 20});

    rec = {screenWidth/2 - 75, 550, 150, 40};
    menu_B[3].initilize ({rec, "Quit game", 20});
}

void initilize_settings_buttons ()
{
    Rectangle rec;
    
    rec = {screenWidth/2 - 75, 250, 75, 40}; // x, y, width, height
    settings_B[0].initilize ({rec, "30", 20}); //position, text, text size
    
    rec = {screenWidth/2 + 25, 250, 75, 40};
    settings_B[1].initilize ({rec, "60", 20});
    
    rec = {screenWidth/2 + 125, 250, 75, 40};
    settings_B[2].initilize ({rec, "90", 20});
    
    rec = {screenWidth/2 + 225, 250, 75, 40};
    settings_B[3].initilize ({rec, "120", 20});
    
    rec = {screenWidth/2 - 75, 350, 75, 40};
    settings_B[4].initilize ({rec, "On", 20});
    
    rec = {screenWidth/2 + 25, 350, 75, 40};
    settings_B[5].initilize ({rec, "Off", 20});
    
    rec = {screenWidth/2 - 75, 450, 150, 40};
    settings_B[6].initilize ({rec, "Single player", 20});
    
    rec = {screenWidth/2 + 125, 450, 150, 40};
    settings_B[7].initilize ({rec, "Multiplayer", 20});
    
    rec = {screenWidth/2 - 75, 550, 150, 40};
    settings_B[8].initilize ({rec, "Arcade", 20});
    
    rec = {screenWidth/2 + 125, 550, 150, 40};
    settings_B[9].initilize ({rec, "Sand box", 20});
    
    rec = {3* screenWidth/4 + 30, 3* screenHeight/4 + 60, 150, 40};
    settings_B[10].initilize ({rec, "Main menu", 20});
}

void initilize_about_pause_lostGame_buttons ()
{
    Rectangle rec;
    
    // about_buttons
    rec = {3* screenWidth/4 + 30, 3* screenHeight/4 + 60, 150, 40}; // x, y, width, height
    about_B[0].initilize ({rec, "Main menu", 20}); //position, text, text size
    
    // pause_buttons
    rec = {screenWidth/2 - 250, screenHeight/2, 150, 40};
    pause_B[0].initilize ({rec, "Resume", 20});
    
    rec = {screenWidth/2 + 100, screenHeight/2, 150, 40};
    pause_B[1].initilize ({rec, "Main menu", 20});
    
    // lostGame_buttons
    rec = {screenWidth/2 - 75, 3* screenHeight/4, 150, 40};
    lostGame_B[0].initilize ({rec, "Continue", 20});
}

/////////////////////////////////////////////////////////////////////////