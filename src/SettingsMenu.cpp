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
								(Rectangle){-W/2.0f, -245, W/2.0f, H},
								[] {Singleton<ScreenManager>::get_instance().toggle_full_screen(1);},
								KEY_NULL,
								[] () -> bool {return IsWindowFullscreen();}));
								
	add_button	(bBuilder.build ("Off", // #1
								(Rectangle){x_of(0) + w_of(0) + HS, y_of(0), W/2.0f, H},
								[] {Singleton<ScreenManager>::get_instance().toggle_full_screen(0);},
								KEY_NULL,
								[] () -> bool {return !IsWindowFullscreen();}));
	
	add_button	(bBuilder.build ("On", // #2
								(Rectangle){-W/2.0f, y_of(1) + h_of(1) + VS, W/2.0f, H},
								[] {activate_setting (SHOW_FPS);},
								KEY_NULL,
								[] () -> bool {return check_setting(SHOW_FPS);}));
								
	add_button	(bBuilder.build ("Off", // #3
								(Rectangle){x_of(2) + w_of(2) + HS, y_of(2), W/2.0f, H},
								[] {deactivate_setting (SHOW_FPS);},
								KEY_NULL,
								[] () -> bool {return !check_setting(SHOW_FPS);}));
	
	add_button	(bBuilder.build ("one player", // #4
								(Rectangle){-W/2.0f, y_of(3) + h_of(3) + VS, W, H},
								[]{
									PLAYER_1.activate(1);
									PLAYER_2.activate(0);
									PLAYER_3.activate(0);
								},
								KEY_NULL,
								[] () -> bool {
									bool res = PLAYER_1.is_active();
									res = (res && !PLAYER_2.is_active());
									res = (res && !PLAYER_3.is_active());
									return res;
								}));
	
	add_button	(bBuilder.build ("two players", // #5
								(Rectangle){x_of(4) + w_of(4) + HS, y_of(4), W, H},
								[]{
									PLAYER_1.activate(1);
									PLAYER_2.activate(1);
									PLAYER_3.activate(0);
								},
								KEY_NULL,
								[] () -> bool {
									bool res = PLAYER_2.is_active();
									res = (res && !PLAYER_3.is_active());
									return res;
								}));
	
	add_button	(bBuilder.build ("three players", // #6
								(Rectangle){x_of(5) + w_of(5) + HS, y_of(4), W, H},
								[]{
									PLAYER_1.activate(1);
									PLAYER_2.activate(1);
									PLAYER_3.activate(1);
									MENUS_BACKGROUND_EFFECTS.launchBall();
								},
								KEY_NULL,
								[] () -> bool {return PLAYER_3.is_active();}));
	
	add_button	(bBuilder.build ("Keyboard", // #7
								(Rectangle){-W/2.0f, y_of(6) + h_of(6) + VS, W, H},
								[]{
									PLAYER_1.set_keyboard_control ({KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT});
									PLAYER_3.set_mouse_control();
								},
								KEY_NULL,
								[] () -> bool {return !PLAYER_1.uses_mouse();}));
	
	add_button	(bBuilder.build ("Mouse", // #8
								(Rectangle){x_of(7) + w_of(7) + HS, y_of(7), W, H},
								[]{
									PLAYER_1.set_mouse_control();
									PLAYER_3.set_keyboard_control ({KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT});
								},
								KEY_NULL,
								[] () -> bool {return PLAYER_1.uses_mouse();}));
	
	add_button	(bBuilder.build ("Arcade", // #9
								(Rectangle){-W/2.0f, y_of(8) + h_of(8) + VS, W, H},
								[] {deactivate_setting (SANDBOX);},
								KEY_NULL,
								[] () -> bool {return !check_setting (SANDBOX);}));
	
	add_button	(bBuilder.build ("Sand box", // #10
								(Rectangle){x_of(9) + w_of(9) + HS, y_of(9), W, H},
								[] {activate_setting (SANDBOX);},
								KEY_NULL,
								[] () -> bool {return check_setting (SANDBOX);}));
	
	add_button	(bBuilder.build ("Easy", // #11
								(Rectangle){x_of(9), y_of(9) + h_of(9) + VS, 3*W/4, H},
								[] {ENEMIES_MANAGER.set_difficulty (EASY);},
								KEY_NULL,
								[] () -> bool {return ENEMIES_MANAGER.get_difficulty() == EASY;}));
	
	add_button	(bBuilder.build ("Medium", // #12
								(Rectangle){x_of(11) + w_of(11) + HS, y_of(11), 3*W/4, H},
								[] {ENEMIES_MANAGER.set_difficulty (MEDIUM);},
								KEY_NULL,
								[] () -> bool {return ENEMIES_MANAGER.get_difficulty() == MEDIUM;}));
	
	add_button	(bBuilder.build ("Hard", // #13
								(Rectangle){x_of(12) + w_of(12) + HS, y_of(12), 3*W/4, H},
								[] {ENEMIES_MANAGER.set_difficulty (HARD);},
								KEY_NULL,
								[] () -> bool {return ENEMIES_MANAGER.get_difficulty() == HARD;}));
	
	add_button	(bBuilder.build ("INSANE", // #14
								(Rectangle){x_of(13) + w_of(13) + HS, y_of(13), 3*W/4, H},
								[] {ENEMIES_MANAGER.set_difficulty (INSANE);},
								KEY_NULL,
								[] () -> bool {return ENEMIES_MANAGER.get_difficulty() == INSANE;}));
	
	add_button	(bBuilder.build ("Main menu", // #15
								(Rectangle){(SCREEN_WIDTH/2.0f) - 150, (SCREEN_HEIGHT/2.0f) - 55, W, H},
								[] {/* loop terminator button, no action */},
								KEY_ESCAPE));
	
	#undef x_of
	#undef y_of
	#undef w_of
	#undef h_of
}

void SettingsMenu::loop ()
{
	while (!buttons.back().is_pressed()){
		Menu::update (CAMERA);
		MENUS_BACKGROUND_EFFECTS.update (GetFrameTime());
		
		BeginDrawing ();
		ClearBackground (WHITE);
		BeginMode2D (CAMERA);
		draw ();
		MENUS_BACKGROUND_EFFECTS.draw();
		EndMode2D ();
		EndDrawing ();
	}
	buttons.back().press(0);
}

void SettingsMenu::draw ()
{
	Menu::draw ();
	draw_message_aligned (buttons[0], msg1, ORANGE);
	draw_message_aligned (buttons[2], msg2, ORANGE);
	draw_message_aligned (buttons[4], msg3, ORANGE);
	draw_message_aligned (buttons[7], msg4, ORANGE);
	draw_message_aligned (buttons[9], msg5, ORANGE);
}