#include "raylib.h"
#include "GameOverMenu.hpp"
#include "ButtonBuilder.hpp"
#include "global_resources.hpp"

GameOverMenu::GameOverMenu ()
{
	ButtonBuilder bBuilder ({BLACK, RED, WHITE}, {BLACK, GREEN, SKYBLUE}, 17);
	
	float W = 125, H = 30; // default width and height for buttons in this menu.
	
	add_button	(bBuilder.build ("Continue",
								(Rectangle){-W/2.0f, SCREEN_HEIGHT/12.0f, W, H},
								[]{
									MENUS_BACKGROUND_EFFECTS.initilize();
									AUDIO_MANAGER.play_menu_music();
								},
								KEY_SPACE));
	
	add_button	(bBuilder.build ("Restart",
								(Rectangle){-W/2.0f, SCREEN_HEIGHT/12.0f + 3*H, W, H},
								[]{
									GAME_WORLD.restart ();
								},
								KEY_ENTER));
}

void GameOverMenu::loop ()
{
	AUDIO_MANAGER.collapse_current_music (1);
	while (!buttons[0].is_pressed() && !buttons[1].is_pressed()){
		Menu::update (CAMERA);
		AUDIO_MANAGER.update (IN_GAME_MENUS_LOOP);
		
		BeginDrawing ();
		ClearBackground (LIGHTGRAY);
		BeginMode2D (CAMERA);
		draw ();
		EndMode2D ();
		EndDrawing ();
	}
	buttons[0].press(0);
	buttons[1].press(0);
	AUDIO_MANAGER.collapse_current_music (0);
}

void GameOverMenu::draw ()
{	
	Menu::draw ();
	if (PLAYER_1.is_active ()) {PLAYER_1.draw_statistics (0);}
	if (PLAYER_2.is_active ()) {PLAYER_2.draw_statistics (1);}
	if (PLAYER_3.is_active ()) {PLAYER_3.draw_statistics (2);}
	draw_message_aligned (buttons[0], msg4, ORANGE, 20);
	draw_message_aligned (buttons[1], msg5, ORANGE, 20);
}