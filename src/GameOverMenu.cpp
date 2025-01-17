#include "raylib.h"
#include "GameOverMenu.hpp"
#include "ButtonBuilder.hpp"
#include "global_resources.hpp"

GameOverMenu::GameOverMenu ()
{
	ButtonBuilder bBuilder ({BLACK, RED, WHITE}, {BLACK, GREEN, SKYBLUE}, 17);
	
	float W = 125, H = 30; // default width and height for buttons in this menu.
	
	add_button	(bBuilder.build ("Restart", // #0
								(Rectangle){-W/2.0f, SCREEN_HEIGHT/6.0f, W, H},
								[]{
									GAME_WORLD.restart ();
								},
								KEY_ENTER));
	
	add_button	(bBuilder.build ("Continue", // #1
								(Rectangle){-W/2.0f, SCREEN_HEIGHT/6.0f + 3*H, W, H},
								[]{
									MENUS_BACKGROUND_EFFECTS.initilize();
									AUDIO_MANAGER.play_menu_music();
								},
								KEY_SPACE));
}

void GameOverMenu::loop ()
{
	AUDIO_MANAGER.collapse_current_music (1);
	while (!buttons[0].is_pressed() && !buttons[1].is_pressed()){
		Menu::update (CAMERA);
		AUDIO_MANAGER.update (IN_GAME_MENUS_LOOP);
		draw ();
	}
	buttons[0].press(0);
	buttons[1].press(0);
	AUDIO_MANAGER.collapse_current_music (0);
}

void GameOverMenu::draw ()
{	
	BeginDrawing ();
	ClearBackground (dark_mode_processor (LIGHTGRAY));
	BeginMode2D (CAMERA);
	
	Menu::draw ();
	DrawText (	TextFormat(	"Difficulty: %s\t\t\t\t\tGame Mode: %s",
							ENEMIES_MANAGER.get_difficulty_string().c_str(),
							ENEMIES_MANAGER.get_game_mode_string().c_str()),
				-SCREEN_WIDTH*0.45f,
				-SCREEN_HEIGHT*0.45f,
				40,
				dark_mode_processor (BLACK));
	if (PLAYER_1.is_active ()) {PLAYER_1.draw_statistics (0);}
	if (PLAYER_2.is_active ()) {PLAYER_2.draw_statistics (1);}
	if (PLAYER_3.is_active ()) {PLAYER_3.draw_statistics (2);}
	draw_message_aligned (buttons[0], msg4, dark_mode_processor (BLACK), 20);
	draw_message_aligned (buttons[1], msg5, dark_mode_processor (BLACK), 20);
	
	EndMode2D ();
	EndDrawing ();
}