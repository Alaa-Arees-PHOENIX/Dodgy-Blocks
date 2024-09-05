#ifndef SETTINGSMENU_DB
#define SETTINGSMENU_DB

#include "Menu.hpp"

class SettingsMenu : public Menu
{
private:
	static constexpr char msg1[] = "Full screen:";
	static constexpr char msg2[] = "Show FPS:";
	static constexpr char msg3[] = "Number of players:";
	static constexpr char msg4[] = "Game mode:";
public:
	SettingsMenu ();
	void loop () override;
	void update (); // this is an overload for Menu::update (const Camera2D&), and not an override...
	void draw () override;
};

#endif // SETTINGSMENU_DB