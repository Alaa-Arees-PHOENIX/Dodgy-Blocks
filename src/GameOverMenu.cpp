#include "raylib.h"
#include "GameOverMenu.hpp"
#include "ButtonBuilder.hpp"
#include "global_resources.hpp"

GameOverMenu::GameOverMenu ()
{
	ButtonBuilder bBuilder ({BLACK, RED, WHITE}, {BLACK, GREEN, SKYBLUE}, 17);
	
	float W = 125, H = 30; // default width and height for buttons in this menu.
	
	add_button	(bBuilder.build ("Continue",
								(Rectangle){-W/2.0f, SCREEN_HEIGHT/4.0f, W, H},
								[]{
									MENUS_BACKGROUND_EFFECTS.initilize();
								},
								KEY_ENTER));
}

void GameOverMenu::loop ()
{
	while (!buttons[0].is_pressed()){
		Menu::update (CAMERA);
		
		BeginDrawing ();
		ClearBackground (LIGHTGRAY);
		BeginMode2D (CAMERA);
		draw ();
		EndMode2D ();
		EndDrawing ();
	}
	buttons[0].press(0);
}

void GameOverMenu::draw ()
{	
	Menu::draw ();
	if (PLAYER_1.is_active ()) {PLAYER_1.draw_statistics (0);}
	if (PLAYER_2.is_active ()) {PLAYER_2.draw_statistics (1);}
	if (PLAYER_3.is_active ()) {PLAYER_3.draw_statistics (2);}
}