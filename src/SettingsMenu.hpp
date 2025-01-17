#ifndef SETTINGSMENU_DB
#define SETTINGSMENU_DB

#include "Menu.hpp"

class SettingsMenu : public Menu
{
public:
	SettingsMenu ();
	void loop () override;
	void draw () override;
	
private:
	static constexpr char msg1[] = "Full screen:";
	static constexpr char msg2[] = "Show FPS:";
	static constexpr char msg3[] = "Number of players:";
	static constexpr char msg4[] = "Red player's controls:";
	static constexpr char msg5[] = "Game mode:";
	static constexpr char msg6[] = "Difficulty:";
};

#endif // SETTINGSMENU_DB