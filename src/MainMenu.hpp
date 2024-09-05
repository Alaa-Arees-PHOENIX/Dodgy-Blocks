#ifndef MAINMENU_DB
#define MAINMENU_DB

#include "Menu.hpp"

class MainMenu : public Menu
{
public:
	MainMenu ();
	void loop () override;
	// void update () override; // no need to override update for main menu.
	// void draw () override; // no need to override draw for main menu.
};

#endif // MAINMENU_DB