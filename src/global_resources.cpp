#include "global_resources.hpp"
#include <cstdint>

uint8_t settings = 0;

void create_globals ()
{
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
}

int random_number (int Min, int Max)
{
    return rand () % (Max - Min + 1) + Min;
}

int random_number (Range range)
{
    return rand () % (range.rMax - range.rMin + 1) + range.rMin;
}