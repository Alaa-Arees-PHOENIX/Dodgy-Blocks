#ifndef PAUSEMENU_DB
#define PAUSEMENU_DB

#include "Menu.hpp"

class PauseMenu : public Menu
{
public:
	PauseMenu ();
	void loop () override;
	// void update () override;
	// void draw () override;
};

#endif // PAUSEMENU_DB