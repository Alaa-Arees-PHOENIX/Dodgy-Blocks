#include "raylib.h"
#include "LostGameMenu.hpp"
#include "ButtonBuilder.hpp"
#include "global_resources.hpp"

LostGameMenu::LostGameMenu ()
{
	ButtonBuilder bBuilder ({BLACK, RED, WHITE}, {BLACK, GREEN, SKYBLUE}, 17);
	
	float W = 125, H = 30; // default width and height for buttons in this menu.
	
	add_button	(bBuilder.build ("Main menu",
								(Rectangle){(SCREEN_WIDTH/2.0f) - 200, (SCREEN_HEIGHT/2.0f) - 100, W, H},
								[] {}));
}

void LostGameMenu::loop ()
{
	
}