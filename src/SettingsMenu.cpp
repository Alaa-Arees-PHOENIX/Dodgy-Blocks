#include "raylib.h"
#include "SettingsMenu.hpp"
#include "ButtonBuilder.hpp"
#include "global_resources.hpp"

SettingsMenu::SettingsMenu ()
{
	ButtonBuilder bBuilder ({BLACK, RED, WHITE}, {BLACK, GREEN, SKYBLUE}, 17);
	
	float W = 125, H = 30; // default width and height for buttons in this menu.
	float VS = 50, HS = 20; // default Vertical/Horizontal Spacing between buttons in this menu.
	// vertical spacing rule: B2.y = B1.y + B1.height + VS (to leave some space)
	// horizontal spacing rule: B2.x = B1.x + B1.width + HS (to leave some space)
	
	#define x_of(n) buttons[n].get_x()
	#define y_of(n) buttons[n].get_y()
	#define w_of(n) buttons[n].get_width()
	#define h_of(n) buttons[n].get_height()
	
	add_button	(bBuilder.build ("On", // #0
								(Rectangle){-W/2.0f, -125, W/2.0f, H},
								[] {Singleton<ScreenManager>::get_instance().toggle_full_screen(1);}));
								
	add_button	(bBuilder.build ("Off", // #1
								(Rectangle){x_of(0) + w_of(0) + HS, y_of(0), W/2.0f, H},
								[] {Singleton<ScreenManager>::get_instance().toggle_full_screen(0);}));
	
	add_button	(bBuilder.build ("On", // #2
								(Rectangle){-W/2.0f, y_of(1) + h_of(1) + VS, W/2.0f, H},
								[] {activate_setting (SHOW_FPS);}));
								
	add_button	(bBuilder.build ("Off", // #3
								(Rectangle){x_of(2) + w_of(2) + HS, y_of(2), W/2.0f, H},
								[] {deactivate_setting (SHOW_FPS);}));
	
	add_button	(bBuilder.build ("Single player", // #4
								(Rectangle){-W/2.0f, y_of(3) + h_of(3) + VS, W, H},
								[] {deactivate_setting (MULTIPLAYER);}));
	
	add_button	(bBuilder.build ("Multiplayer", // #5
								(Rectangle){x_of(4) + w_of(4) + HS, y_of(4), W, H},
								[] {activate_setting (MULTIPLAYER);}));
	
	add_button	(bBuilder.build ("Arcade", // #6
								(Rectangle){-W/2.0f, y_of(5) + h_of(5) + VS, W, H},
								[] {deactivate_setting (SANDBOX);}));
	
	add_button	(bBuilder.build ("Sand box", // #7
								(Rectangle){x_of(6) + w_of(6) + HS, y_of(6), W, H},
								[] {activate_setting (SANDBOX);}));
	
	add_button	(bBuilder.build ("Main menu", // #8
								(Rectangle){(SCREEN_WIDTH/2.0f) - 200, (SCREEN_HEIGHT/2.0f) - 75, W, H},
								[] {},
								KEY_ESCAPE));
	
	#undef x_of
	#undef y_of
	#undef w_of
	#undef h_of
}

void SettingsMenu::loop ()
{
	while (!buttons.back().is_pressed()){
		update ();
		
		BeginDrawing ();
		ClearBackground (WHITE);
		BeginMode2D (CAMERA);
		draw ();
		EndMode2D ();
		EndDrawing ();
	}
	buttons.back().press(0);
}

void SettingsMenu::update ()
{
	Menu::update (CAMERA);
	
	if (IsWindowFullscreen ())			{buttons[0].activate(1); buttons[0].change_colors();}
	else 								{buttons[1].activate(1); buttons[1].change_colors();}
	if (check_setting (SHOW_FPS))		{buttons[2].activate(1); buttons[2].change_colors();}
	else 								{buttons[3].activate(1); buttons[3].change_colors();}
	if (!check_setting (MULTIPLAYER))	{buttons[4].activate(1); buttons[4].change_colors();}
	else 								{buttons[5].activate(1); buttons[5].change_colors();}
	if (!check_setting (SANDBOX))		{buttons[6].activate(1); buttons[6].change_colors();}
	else 								{buttons[7].activate(1); buttons[7].change_colors();}
}

void SettingsMenu::draw ()
{
	Menu::draw ();
	draw_message_aligned (buttons[0], msg1, ORANGE);
	draw_message_aligned (buttons[2], msg2, ORANGE);
	draw_message_aligned (buttons[4], msg3, ORANGE);
	draw_message_aligned (buttons[6], msg4, ORANGE);
}