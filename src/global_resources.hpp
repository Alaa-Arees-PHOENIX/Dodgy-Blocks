#ifndef GLOBAL_RESOURCES_DB
#define GLOBAL_RESOURCES_DB

#include <cstdint>
#include "raylib.h"
#include "Singleton.hpp"
#include "GameWorld.hpp"
#include "ScreenManager.hpp"
#include "MainMenu.hpp"
#include "SettingsMenu.hpp"
#include "AboutMenu.hpp"
#include "PauseMenu.hpp"
#include "GameOverMenu.hpp"
#include "Timer.hpp"
#include "EnemiesManager.hpp"
#include "PlayersManager.hpp"
#include "types.hpp"
#include "Logger.hpp"
#include "MenusBackgroundEffects.hpp"
#include "AudioManager.hpp"

struct Rectangle;
struct Vector2;

////////////// USEFUL MACROS /////////////////////
#define SCREEN_WIDTH	Singleton<ScreenManager>::get_instance().get_default_screen_width()
#define SCREEN_HEIGHT	Singleton<ScreenManager>::get_instance().get_default_screen_height()

#define MONITOR_WIDTH	Singleton<ScreenManager>::get_instance().get_monitor_width()
#define MONITOR_HEIGHT	Singleton<ScreenManager>::get_instance().get_monitor_height()

#define CURRENT_SCREEN_WIDTH	Singleton<ScreenManager>::get_instance().get_current_screen_width()
#define CURRENT_SCREEN_HEIGHT	Singleton<ScreenManager>::get_instance().get_current_screen_height()

#define CAMERA Singleton<ScreenManager>::get_instance().get_camera()

#define MAIN_MENU		Singleton<MainMenu>::get_instance()
#define SETTINGS_MENU	Singleton<SettingsMenu>::get_instance()
#define ABOUT_MENU		Singleton<AboutMenu>::get_instance()
#define PAUSE_MENU		Singleton<PauseMenu>::get_instance()
#define GAME_OVER_MENU	Singleton<GameOverMenu>::get_instance()

#define TIMER Singleton<Timer>::get_instance()

#define GAME_WORLD Singleton<GameWorld>::get_instance()

#define ENEMIES_MANAGER Singleton<EnemiesManager>::get_instance()

#define PLAYERS_MANAGER	Singleton<PlayersManager>::get_instance()
#define PLAYER_1		Singleton<PlayersManager>::get_instance().P(0)
#define PLAYER_2		Singleton<PlayersManager>::get_instance().P(1)
#define PLAYER_3		Singleton<PlayersManager>::get_instance().P(2)

#define LOGGER Singleton<Logger>::get_instance()

#define MENUS_BACKGROUND_EFFECTS Singleton<MenusBackgroundEffects>::get_instance()

#define AUDIO_MANAGER Singleton<AudioManager>::get_instance()

// // // // // // // // // GLOBAL VARIABLES:
extern uint8_t settings; // using bitmask to toggle game settings
constexpr char TITLE[] = "Dodgy Blocks";

// // // // // // // // // GLOBAL METHODS:
// NOTE: some of these functions are declared and defined here to be inline
// (they are not defined in global_resources.cpp like normal functions)

inline bool check_setting (Settings s)		{return ((settings & s) == s);} // checks whether an option is active or not
inline void activate_setting (Settings s)	{settings = (settings | s);} // turns an option on
inline void deactivate_setting (Settings s)	{settings = (settings & (~s));} // turns an option off

void create_globals (); // Istantiate global objects with `Singleton<T>`.
void destroy_globals (); // destroy all globals istantiated above.
int random_number (int Min, int Max);
int random_number (Range range);
std::string to_string (const Range&);
std::string to_string (const Rectangle&);
std::string to_string (const Vector2&);
double lerp (float initialPos, float targetPos, float lerpSpeed);

#endif // GLOBAL_RESOURCES_DB
