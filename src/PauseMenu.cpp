#include "raylib.h"
#include "PauseMenu.hpp"
#include "ButtonBuilder.hpp"
#include "global_resources.hpp"

PauseMenu::PauseMenu ()
{
	ButtonBuilder bBuilder ({BLACK, RED, WHITE}, {BLACK, GREEN, SKYBLUE}, 17);
	
	float W = 125, H = 30; // default width and height for buttons in this menu.
	
	add_button	(bBuilder.build ("Resume",
								(Rectangle){-SCREEN_WIDTH/6.0f - W/2.0f, 0, W, H},
								[] {/* loop terminator button, no action */},
								KEY_ENTER));
	
	add_button	(bBuilder.build ("Main menu",
								(Rectangle){SCREEN_WIDTH/6.0f - W/2.0f, 0, W, H},
								[] {GAME_WORLD.terminate();}));
}

void PauseMenu::loop ()
{
	while (!buttons[0].is_pressed() && !buttons[1].is_pressed()){
		Menu::update (CAMERA);
		
		BeginDrawing ();
		ClearBackground (LIGHTGRAY);
		BeginMode2D (CAMERA);
		Menu::draw ();
		EndMode2D ();
		EndDrawing ();
	}
	buttons[0].press(0);
	buttons[1].press(0);
}