#include "raylib.h"
#include "PauseMenu.hpp"
#include "ButtonBuilder.hpp"
#include "global_resources.hpp"

PauseMenu::PauseMenu ()
{
	ButtonBuilder bBuilder ({BLACK, RED, WHITE}, {BLACK, GREEN, SKYBLUE}, 17);
	
	float W = 125, H = 30; // default width and height for buttons in this menu.
	
	add_button	(bBuilder.build ("Resume", // #0
								(Rectangle){-SCREEN_WIDTH/6.0f - W/2.0f, 0, W, H},
								[] {},
								KEY_ENTER));
	
	add_button	(bBuilder.build ("Main menu", // #1
								(Rectangle){SCREEN_WIDTH/6.0f - W/2.0f, 0, W, H},
								[]{GAME_WORLD.terminate();}));
}

void PauseMenu::loop ()
{
	AUDIO_MANAGER.collapse_current_music (1);
	while (true){
		Menu::update (CAMERA);
		AUDIO_MANAGER.update (IN_GAME_MENUS_LOOP);
		if (buttons[0].is_pressed()){
			AUDIO_MANAGER.collapse_current_music (0);
			break;
		}
		if (buttons[1].is_pressed()){
			AUDIO_MANAGER.collapse_current_music (1);
			break;
		}
		
		BeginDrawing ();
		ClearBackground (dark_mode_processor (LIGHTGRAY));
		BeginMode2D (CAMERA);
		Menu::draw ();
		EndMode2D ();
		EndDrawing ();
	}
	buttons[0].press(0);
	buttons[1].press(0);
}