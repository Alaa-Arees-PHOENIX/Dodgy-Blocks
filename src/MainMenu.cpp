#include "raylib.h"
#include "Menu.hpp"
#include "MainMenu.hpp"
#include "ButtonBuilder.hpp"
#include "global_resources.hpp"

MainMenu::MainMenu ()
{
/* 		@REMINDERS:
	Button ButtonBuilder::build (std::string text, Rectangle bounds, bool withEffects = 0,
								KeyboardKey alternativeKey = KEY_NULL);

	Button::Button (Rectangle bounds, std::string text, int textSize, 
				std::tuple <Color, Color, Color> normalColors, 
				std::tuple <Color, Color, Color> activeColors,
				bool withEffects = 0,
				KeyboardKey alternativeKey = KEY_NULL);
			
	raylib's Rectangle type is like this: {x, y, width, height}
        
*/
	
	ButtonBuilder bBuilder ({BLACK, RED, WHITE}, {BLACK, GREEN, SKYBLUE}, 17);
	
	float W = 125, H = 30; // default width and height for buttons in this menu.
	float VS = 55; // default vertical spacing between buttons in this menu.
	// vertical spacing rule: B2.y = B1.y + B1.height + S (to leave some space)
	
    add_button	(bBuilder.build ("Play",
								(Rectangle){-W/2.0f, -75, W, H},
								[]{
									AUDIO_MANAGER.stop_menu_music ();
									GAME_WORLD.loop();
								},
								KEY_ENTER));
								
	add_button	(bBuilder.build ("Settings",
								(Rectangle){-W/2.0f, buttons[0].get_y() + H + VS, W, H},
								[]{
									MENUS_BACKGROUND_EFFECTS.launch_cannon();
									MENUS_BACKGROUND_EFFECTS.animate_recs();
									SETTINGS_MENU.loop();
								}));
								
    add_button	(bBuilder.build ("About us",
								(Rectangle){-W/2.0f, buttons[1].get_y() + H + VS, W, H},
								[]{
									MENUS_BACKGROUND_EFFECTS.launch_cannon();
									MENUS_BACKGROUND_EFFECTS.animate_recs();
									ABOUT_MENU.loop();
								}));
								
    add_button	(bBuilder.build ("Quit game",
								(Rectangle){-W/2.0f, buttons[2].get_y() + H + VS, W, H},
								[] {/* loop terminator button, no action */},
								KEY_ESCAPE));
	
	add_button	(bBuilder.build ("Music",
								(Rectangle){-SCREEN_WIDTH*0.45f + W/4.0f, SCREEN_HEIGHT*0.30f - 4*H, W/2.0f, H},
								[]{
									MENUS_BACKGROUND_EFFECTS.launch_cannon();
									toggle_setting (ENABLE_MUSIC);
									if (check_setting (ENABLE_MUSIC)){
										AUDIO_MANAGER.play_menu_music();
									}else {AUDIO_MANAGER.stop_menu_music();}
								},
								KEY_NULL,
								[] () -> bool{
									return check_setting (ENABLE_MUSIC);
								}));
	
	add_button	(bBuilder.build ("SFX",
								(Rectangle){-SCREEN_WIDTH*0.45f + W/4.0f, SCREEN_HEIGHT*0.30f - 2*H, W/2.0f, H},
								[]{
									MENUS_BACKGROUND_EFFECTS.launch_cannon();
									toggle_setting (ENABLE_SFX);
								},
								KEY_NULL,
								[] () -> bool{
									return check_setting (ENABLE_SFX);
								}));
	
	add_button	(bBuilder.build ("Dark Mode",
								(Rectangle){-SCREEN_WIDTH*0.45f, SCREEN_HEIGHT*0.30f, W, H},
								[]{
									MENUS_BACKGROUND_EFFECTS.launch_cannon();
									COLORS_MANAGER.toggle_dark_mode ();
								},
								KEY_NULL,
								[] () -> bool{
									return COLORS_MANAGER.is_dark_mode_enabled ();
								}));
}

void MainMenu::loop ()
{
	MENUS_BACKGROUND_EFFECTS.initilize();
	MENUS_BACKGROUND_EFFECTS.animate_recs();
	while (!buttons[3].is_pressed()){
		Menu::update (CAMERA);
		MENUS_BACKGROUND_EFFECTS.update (GetFrameTime());
		AUDIO_MANAGER.update (OUT_GAME_MENUS_LOOP);
		
		#if defined (DEBUG)
			if (IsKeyPressed (KEY_B)){
				int breakPoint = 0;
			}
			LOGGER.update(GetFrameTime());
		#endif
		
		BeginDrawing ();
		ClearBackground (dark_mode_processor (RAYWHITE));
		BeginMode2D (CAMERA);
		MENUS_BACKGROUND_EFFECTS.draw();
		Menu::draw ();
		DrawText (TITLE, -MeasureText (TITLE, 60)/2.0f, -SCREEN_HEIGHT/3.0f - 50, 60, RED);
		EndMode2D ();
		EndDrawing ();
	}
	buttons[3].press(0);
}

