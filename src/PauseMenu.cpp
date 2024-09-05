#include "raylib.h"
#include "PauseMenu.hpp"
#include "ButtonBuilder.hpp"
#include "global_resources.hpp"

PauseMenu::PauseMenu ()
{
	ButtonBuilder bBuilder ({BLACK, RED, WHITE}, {BLACK, GREEN, SKYBLUE}, 17);
	
	float W = 125, H = 30; // default width and height for buttons in this menu.
	
	add_button	(bBuilder.build ("Resume",
								(Rectangle){-SCREEN_WIDTH/4.0f - W/2.0f, 0, W, H},
								[] {}));
	
	add_button	(bBuilder.build ("Main menu",
								(Rectangle){SCREEN_WIDTH/4.0f - W/2.0f, 0, W, H},
								[] {}));
}

void PauseMenu::loop ()
{
	
}