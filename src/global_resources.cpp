#include "raylib.h"
#include "global_resources.hpp"
#include <cstdint>

uint8_t settings = (ENABLE_MUSIC | ENABLE_SFX);

void create_globals ()
{
	/* Logger MUST be created first and destroyed last (when 'DEBUG' is defined). */
	#if defined(DEBUG)
		Singleton<Logger>::create_instance ();
	#endif
	Singleton<ScreenManager>::create_instance ();
	Singleton<GameWorld>::create_instance ();
	Singleton<MainMenu>::create_instance ();
	Singleton<SettingsMenu>::create_instance ();
	Singleton<AboutMenu>::create_instance ();
	Singleton<PauseMenu>::create_instance ();
	Singleton<GameOverMenu>::create_instance ();
	Singleton<Timer>::create_instance ();
	Singleton<EnemiesManager>::create_instance ();
	Singleton<PlayersManager>::create_instance ();
	Singleton<MenusBackgroundEffects>::create_instance();
	Singleton<AudioManager>::create_instance();
	Singleton<ColorsManager>::create_instance();
}

void destroy_globals ()
{
	Singleton<MainMenu>::destroy_instance ();
	Singleton<SettingsMenu>::destroy_instance ();
	Singleton<AboutMenu>::destroy_instance ();
	Singleton<PauseMenu>::destroy_instance ();
	Singleton<GameOverMenu>::destroy_instance ();
	Singleton<GameWorld>::destroy_instance ();
	Singleton<ScreenManager>::destroy_instance ();
	Singleton<Timer>::destroy_instance ();
	Singleton<EnemiesManager>::destroy_instance ();
	Singleton<PlayersManager>::destroy_instance ();
	Singleton<MenusBackgroundEffects>::destroy_instance();
	Singleton<AudioManager>::destroy_instance();
	Singleton<ColorsManager>::destroy_instance();
	#if defined(DEBUG)
		Singleton<Logger>::destroy_instance ();
	#endif
}

int random_number (int Min, int Max)
{
    return rand () % (Max - Min + 1) + Min;
}

int random_number (Range range)
{
    return rand () % (range.rMax - range.rMin + 1) + range.rMin;
}

std::string to_string (const Range& r)
{
	std::string s = "{" + std::to_string(r.rMin) + ", " + std::to_string(r.rMax) + "}";
	return s;
}

std::string to_string (const Rectangle& r)
{
	std::string s = "{" + std::to_string(r.x) + ", " + std::to_string(r.y) + ", " +
					std::to_string(r.width) + ", " + std::to_string(r.height) + "}";
	return s;
}

std::string to_string (const Vector2& v)
{
	std::string s = "{" + std::to_string(v.x) + ", " + std::to_string(v.y) + "}";
	return s;
}

double lerp (float initialPos, float targetPos, float lerpSpeed)
{
    return targetPos*(1-lerpSpeed) + initialPos*lerpSpeed;
}