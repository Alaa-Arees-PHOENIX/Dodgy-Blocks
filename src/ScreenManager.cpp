#include <cmath>
#include "raylib.h"
#include "ScreenManager.hpp"

ScreenManager::ScreenManager (bool initialFullScreen)
{	
	InitWindow (SCREEN_WIDTH, SCREEN_HEIGHT, "Dodgy Blocks");
	int monitor = GetCurrentMonitor ();
	monitorWidth = GetMonitorWidth (monitor);
	monitorHeight = GetMonitorHeight (monitor);
	SetWindowPosition ((monitorWidth/2) - (SCREEN_WIDTH/2), (monitorHeight/2) - (SCREEN_HEIGHT/2));
	
	SetConfigFlags (FLAG_VSYNC_HINT);
	SetTargetFPS (GetMonitorRefreshRate (monitor));
	
	camera.zoom = 1.0f;
	camera.target = {0, 0};
	camera.offset = {get_current_screen_width()/2.0f, get_current_screen_height()/2.0f};
	
	#if defined (PLATFORM_DESKTOP)
		toggle_full_screen (initialFullScreen);
	#else
		toggle_full_screen (1);
	#endif
}

/* 		@PARAMS
*	bool on: 1 turn full screen on, 0 turn it off
*/
void ScreenManager::toggle_full_screen (bool on)
{
	if (on && (!IsWindowFullscreen())){
		SetWindowSize (monitorWidth, monitorHeight);
		ToggleFullscreen ();
		camera.zoom = std::min ((float)monitorWidth/SCREEN_WIDTH, (float)monitorHeight/SCREEN_HEIGHT);
		}
	else if ((!on) && IsWindowFullscreen()){
		ToggleFullscreen ();
		SetWindowSize (SCREEN_WIDTH, SCREEN_HEIGHT);
		camera.zoom = 1.0f;
		SetWindowPosition ((monitorWidth/2) - (SCREEN_WIDTH/2), (monitorHeight/2) - (SCREEN_HEIGHT/2));
	}
	
	camera.offset = {get_current_screen_width()/2.0f, get_current_screen_height()/2.0f};
}