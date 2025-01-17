#include "raylib.h"
#include "GameWorld.hpp"
#include "global_resources.hpp"
#include "MotiveCreature.hpp"
#include "Player.hpp"
#include "Button.hpp"
#include "Menu.hpp"

GameWorld::GameWorld ()
{
	
}

void GameWorld::loop ()
{
	Loop_Beggining:
	PLAYER_1.initilize();
	PLAYER_2.initilize();
	PLAYER_3.initilize();
	TIMER.reset();
	ENEMIES_MANAGER.reset();
	gameIsRunning = 1;
	shouldRestartGame = 0;
	AUDIO_MANAGER.collapse_current_music (0);
	while (gameIsRunning){
		update (GetFrameTime ());
		draw ();
		if (IsKeyReleased (KEY_ESCAPE)) {PAUSE_MENU.loop();}
	}
	GAME_OVER_MENU.loop ();
	if (shouldRestartGame) {goto Loop_Beggining;}
	AUDIO_MANAGER.collapse_current_music (0);
}

void GameWorld::update (float dt)
{
	PLAYERS_MANAGER.update (dt);
	if (!ENEMIES_MANAGER.is_game_mode_set_to (SANDBOX)){
		TIMER.update (dt);
		ENEMIES_MANAGER.update (dt);
	}
	AUDIO_MANAGER.update (GAME_LOOP);
	
	#if defined (DEBUG)
		if (IsKeyPressed (KEY_B)){
			if (IsWindowFullscreen ()) {ToggleFullscreen ();}
			int breakPoint = 0;
		}
		if (IsKeyDown (KEY_ONE)) {Singleton<ScreenManager>::get_instance().toggle_full_screen (0);}
		if (IsKeyDown (KEY_TWO)) {Singleton<ScreenManager>::get_instance().toggle_full_screen (1);}
		LOGGER.update(GetFrameTime());
	#endif
}

void GameWorld::draw ()
{
	BeginDrawing ();
	ClearBackground (dark_mode_processor (RAYWHITE));
	BeginMode2D (CAMERA);
	
	
	PLAYERS_MANAGER.draw ();
	if (!ENEMIES_MANAGER.is_game_mode_set_to (SANDBOX)){
		TIMER.draw ();
		ENEMIES_MANAGER.draw ();
	}
	if (check_setting (SHOW_FPS)){
		DrawText (TextFormat("%d", GetFPS()), -0.45f*SCREEN_WIDTH, -0.45f*SCREEN_HEIGHT, 17, GREEN);
	}
	
	EndMode2D ();
	#if defined (DEBUG)
		draw_debug ();
	#endif
	EndDrawing ();
}

void GameWorld::terminate ()
{
	gameIsRunning = 0;
}

void GameWorld::restart ()
{
	shouldRestartGame = 1;
}


#if defined (DEBUG)
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
	
	DrawText (TextFormat ("%f", GetScreenToWorld2D (PLAYER_1.get_pos(), CAMERA).x), v1.x, v1.y, 20, RED);
	DrawText (TextFormat ("%f", GetScreenToWorld2D (PLAYER_1.get_pos(), CAMERA).y), v2.x, v2.y, 20, RED);
	DrawText (TextFormat ("%f", GetWorldToScreen2D (PLAYER_1.get_pos(), CAMERA).x), v3.x, v3.y, 20, RED);
	DrawText (TextFormat ("%f", GetWorldToScreen2D (PLAYER_1.get_pos(), CAMERA).y), v4.x, v4.y, 20, RED);
	
	DrawText (TextFormat ("%f", PLAYER_1.get_pos().x), v5.x, v5.y, 20, RED);
	DrawText (TextFormat ("%f", PLAYER_1.get_posY()), v6.x, v6.y, 20, RED);
	// why 5472 screen width to world??
	DrawText (TextFormat ("%f", GetMousePosition().x), 100, 350, 20, GREEN);
	DrawText (TextFormat ("%f", GetMousePosition().y), 500, 350, 20, GREEN);
}
#endif
