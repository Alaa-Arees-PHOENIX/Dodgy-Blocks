#include "raylib.h"
#include "AboutMenu.hpp"
#include "ButtonBuilder.hpp"
#include "global_resources.hpp"

AboutMenu::AboutMenu ()
{
	ButtonBuilder bBuilder ({BLACK, RED, WHITE}, {BLACK, GREEN, SKYBLUE}, 17);
	
	float W = 125, H = 30; // default width and height for buttons in this menu.
	
	add_button	(bBuilder.build ("Main menu",
								(Rectangle){(SCREEN_WIDTH/2.0f) - 200, (SCREEN_HEIGHT/2.0f) - 100, W, H},
								[]{
									MENUS_BACKGROUND_EFFECTS.launchCannon();
									MENUS_BACKGROUND_EFFECTS.animate_recs();
								},
								KEY_ESCAPE));
}

void AboutMenu::loop ()
{
	while (!buttons.back().is_pressed()){
		Menu::update (CAMERA);
		MENUS_BACKGROUND_EFFECTS.update (GetFrameTime());
		
		BeginDrawing ();
		ClearBackground (WHITE);
		BeginMode2D (CAMERA);
		MENUS_BACKGROUND_EFFECTS.draw ();
		draw ();
		EndMode2D ();
		EndDrawing ();
	}
	buttons.back().press(0);
}

void AboutMenu::draw ()
{
	Menu::draw ();
	DrawText (TITLE, -MeasureText (TITLE, 60)/2.0f, -SCREEN_HEIGHT/3.0f - 50, 60, RED);
	DrawText (msg1, -SCREEN_WIDTH/3.0f, -100, 25, ORANGE);
	DrawText (msg2, -SCREEN_WIDTH/3.0f, -63, 25, ORANGE);
	DrawText (msg3, -SCREEN_WIDTH/3.0f, -26, 25, ORANGE);
	DrawText (msg4, -SCREEN_WIDTH/3.0f, 122, 25, ORANGE);
}