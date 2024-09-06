#include "global_resources.hpp"
#include <cstdint>
#include "raylib.h"
#include "Singleton.hpp"
#include "World.hpp"
#include "ScreenManager.hpp"

uint8_t settings = 0;

void create_globals (bool screenMode)
{
	Singleton<ScreenManager>::set_instance (new ScreenManager (screenMode));
	Singleton<World>::create_instance ();
	Singleton<MainMenu>::create_instance ();
	Singleton<SettingsMenu>::create_instance ();
	Singleton<AboutMenu>::create_instance ();
	Singleton<PauseMenu>::create_instance ();
	Singleton<LostGameMenu>::create_instance ();
	Singleton<Timer>::create_instance ();
	Singleton<EnemiesManager>::create_instance ();
}

void destroy_globals ()
{
	Singleton<MainMenu>::destroy_instance ();
	Singleton<SettingsMenu>::destroy_instance ();
	Singleton<AboutMenu>::destroy_instance ();
	Singleton<PauseMenu>::destroy_instance ();
	Singleton<LostGameMenu>::destroy_instance ();
	Singleton<World>::destroy_instance ();
	Singleton<ScreenManager>::destroy_instance ();
	Singleton<Timer>::destroy_instance ();
	Singleton<EnemiesManager>::destroy_instance ();
}

int random_number (int Min, int Max)
{
    return rand () % (Max - Min + 1) + Min;
}