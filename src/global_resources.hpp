#ifndef GLOBAL_RESOURCES_DB
#define GLOBAL_RESOURCES_DB

#include <cstdint>
#include "raylib.h"
#include "Singleton.hpp"
#include "World.hpp"
#include "ScreenManager.hpp"
#include "MainMenu.hpp"
#include "SettingsMenu.hpp"
#include "AboutMenu.hpp"
#include "PauseMenu.hpp"
#include "LostGameMenu.hpp"
#include "Timer.hpp"
#include "EnemiesManager.hpp"

////////////// USEFUL MACROS /////////////////////
#define SCREEN_WIDTH Singleton<ScreenManager>::get_instance().get_default_screen_width()
#define SCREEN_HEIGHT Singleton<ScreenManager>::get_instance().get_default_screen_height()

#define MONITOR_WIDTH Singleton<ScreenManager>::get_instance().get_monitor_width()
#define MONITOR_HEIGHT Singleton<ScreenManager>::get_instance().get_monitor_height()

#define CURRENT_SCREEN_WIDTH Singleton<ScreenManager>::get_instance().get_current_screen_width()
#define CURRENT_SCREEN_HEIGHT Singleton<ScreenManager>::get_instance().get_current_screen_height()

#define CAMERA Singleton<ScreenManager>::get_instance().get_camera()

#define MAIN_MENU Singleton<MainMenu>::get_instance()
#define SETTINGS_MENU Singleton<SettingsMenu>::get_instance()
#define ABOUT_MENU Singleton<AboutMenu>::get_instance()
#define PAUSE_MENU Singleton<PauseMenu>::get_instance()
#define LOST_GAME_MENU Singleton<LostGameMenu>::get_instance()

#define TIMER Singleton<Timer>::get_instance()

#define WORLD Singleton<World>::get_instance()

#define ENEMIES_MANAGER Singleton<EnemiesManager>::get_instance()

// // // // // // // // // GLOBAL TYPES:
enum Directions {UP_DIR, DOWN_DIR, LEFT_DIR, RIGHT_DIR};
enum Settings
{
	MULTIPLAYER		=	1 << 0,
	SANDBOX			=	1 << 1,
	SHOW_FPS		=	1 << 2
};

// // // // // // // // // GLOBAL VARIABLES:
extern uint8_t settings; // using bitmask to toggle game settings
constexpr char TITLE[] = "Dodgy Blocks";

// // // // // // // // // GLOBAL METHODS:
// NOTE: some of these functions are declared and defined here to be inline
// (they are not defined in global_resources.cpp like normal functions)

inline bool check_setting (Settings s)		{return ((settings & s) == s);} // checks whether an option is active or not
inline void activate_setting (Settings s)	{settings = (settings | s);} // turns an option on
inline void deactivate_setting (Settings s)	{settings = (settings & (~s));} // turns an option off

void create_globals (bool screenMode); // istantiate global objects with `Singleton<T>`.
void destroy_globals (); // destroy all globals istantiated above.
int random_number (int Min, int Max);

#endif // GLOBAL_RESOURCES_DB
