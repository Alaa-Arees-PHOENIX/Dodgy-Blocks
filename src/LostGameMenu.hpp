#ifndef LOSTGAMEMENU_DB
#define LOSTGAMEMENU_DB

#include "Menu.hpp"

class LostGameMenu : public Menu
{
public:
	LostGameMenu ();
	void loop ()  override;
	// void update () override;
	// void draw () override;
};

#endif // LOSTGAMEMENU_DB