#ifndef PAUSEMENU_DB
#define PAUSEMENU_DB

#include "Menu.hpp"

class PauseMenu : public Menu
{
public:
	PauseMenu ();
	void loop () override;
};

#endif // PAUSEMENU_DB