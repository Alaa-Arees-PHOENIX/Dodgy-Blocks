#include "raylib.h"
#include "GameWorld.hpp"
#include "global_resources.hpp"
#include "MotiveCreature.hpp"
#include "Player.hpp"
#include "Button.hpp"
#include "Menu.hpp"

GameWorld::GameWorld ()
	:	p1 (Player ({1200, 1200}, {3600, 3600}, 1, RED)),
		p2 (Player ({2000, 2000}, {200, 200}, 1, BLUE))
{
	// setup players:
	p1.set_controls ({KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT});
	p2.set_controls ({KEY_W, KEY_S, KEY_A, KEY_D});
}

void GameWorld::loop ()
{
	p1.initilize();
	p2.initilize();
	TIMER.reset();
	ENEMIES_MANAGER.reset();
	ClearBackground (WHITE);
	while (!p1.is_dead()){ //TODO: while(!endGame && !lostGame)
		update (GetFrameTime ());
		draw ();
		if (IsKeyReleased (KEY_ESCAPE)) {return;}
		if (IsKeyPressed (KEY_ENTER)){
			int breakPoint = 0;
		}
		// if (WindowShouldClose ()) {PAUSE_MENU.loop ();}
		// if (WindowShouldClose ()) {Singleton<MenusManager>::get_instance().pauseMenu_loop ();}
	}
}

void GameWorld::update (float dt)
{
	p1.update (dt);
	if (check_setting (MULTIPLAYER)) {p2.update (dt);}
	if (!check_setting (SANDBOX)){
		TIMER.update (dt);
		ENEMIES_MANAGER.update (dt);
	}
}

void GameWorld::draw ()
{
	BeginDrawing ();
	ClearBackground (WHITE);
	BeginMode2D (CAMERA);
	
	if (IsKeyDown (KEY_ONE)) {Singleton<ScreenManager>::get_instance().toggle_full_screen (0);}
	if (IsKeyDown (KEY_TWO)) {Singleton<ScreenManager>::get_instance().toggle_full_screen (1);}
	p1.draw ();
	if (check_setting (MULTIPLAYER)) {p2.draw ();}
	if (!check_setting (SANDBOX)){
		TIMER.draw ();
		ENEMIES_MANAGER.draw ();
	}
	if (check_setting (SHOW_FPS)) {DrawText (TextFormat("%d", GetFPS()), -0.45f*SCREEN_WIDTH, -0.45f*SCREEN_HEIGHT, 17, GREEN);}
	
	EndMode2D ();
	#if defined (DEBUG)
		draw_debug ();
	#endif
	EndDrawing ();
}



void GameWorld::draw_debug ()
{
	Vector2 v1 = {100, 200}, v2 = {500, 200}, v3 = {100, 250}, v4 = {500, 250};
	Vector2 v5 = {100, 300}, v6 = {500, 300};
	
	// v1 = GetWorldToScreen2D ({100, 200}, CAMERA);
	// v2 = GetWorldToScreen2D ({500, 200}, CAMERA);
	// v3 = GetWorldToScreen2D ({100, 250}, CAMERA);
	// v4 = GetWorldToScreen2D ({500, 250}, CAMERA);
	
	// v1 = GetScreenToWorld2D ({100, 200}, CAMERA);
	// v2 = GetScreenToWorld2D ({500, 200}, CAMERA);
	// v3 = GetScreenToWorld2D ({100, 250}, CAMERA);
	// v4 = GetScreenToWorld2D ({500, 250}, CAMERA);
	
	DrawText (TextFormat ("%f", GetScreenToWorld2D (p1.get_pos(), CAMERA).x), v1.x, v1.y, 20, RED);
	DrawText (TextFormat ("%f", GetScreenToWorld2D (p1.get_pos(), CAMERA).y), v2.x, v2.y, 20, RED);
	DrawText (TextFormat ("%f", GetWorldToScreen2D (p1.get_pos(), CAMERA).x), v3.x, v3.y, 20, RED);
	DrawText (TextFormat ("%f", GetWorldToScreen2D (p1.get_pos(), CAMERA).y), v4.x, v4.y, 20, RED);
	
	DrawText (TextFormat ("%f", p1.get_pos().x), v5.x, v5.y, 20, RED);
	DrawText (TextFormat ("%f", p1.get_posY()), v6.x, v6.y, 20, RED);
	// why 5472 screen width to world??
	DrawText (TextFormat ("%f", GetMousePosition().x), 100, 350, 20, GREEN);
	DrawText (TextFormat ("%f", GetMousePosition().y), 500, 350, 20, GREEN);
}